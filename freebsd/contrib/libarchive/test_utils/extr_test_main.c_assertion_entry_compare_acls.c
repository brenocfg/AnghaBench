#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct archive_test_acl_t {int type; int permset; int tag; int qual; char const* name; } ;
struct archive_entry {int dummy; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  marker ;

/* Variables and functions */
 int ARCHIVE_ENTRY_ACL_GROUP_OBJ ; 
 int ARCHIVE_ENTRY_ACL_OTHER ; 
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
 int ARCHIVE_ENTRY_ACL_USER_OBJ ; 
 int ARCHIVE_EOF ; 
 int archive_entry_acl_next (struct archive_entry*,int,int*,int*,int*,int*,char const**) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 scalar_t__ archive_test_acl_match (struct archive_test_acl_t*,int,int,int,int,char const*) ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,...) ; 
 int /*<<< orphan*/  free (int*) ; 
 int* malloc (int) ; 

int
assertion_entry_compare_acls(const char *file, int line,
    struct archive_entry *ae, struct archive_test_acl_t *acls, int cnt,
    int want_type, int mode)
{
	int *marker;
	int i, r, n, ret;
	int type, permset, tag, qual;
	int matched;
	const char *name;

	assertion_count(file, line);

	ret = 0;
	n = 0;
	marker = malloc(sizeof(marker[0]) * cnt);

	for (i = 0; i < cnt; i++) {
		if ((acls[i].type & want_type) != 0) {
			marker[n] = i;
			n++;
		}
	}

	if (n == 0) {
		failure_start(file, line, "No ACL's to compare, type mask: %d",
		    want_type);
		return (1);
	}

	while (0 == (r = archive_entry_acl_next(ae, want_type,
			 &type, &permset, &tag, &qual, &name))) {
		for (i = 0, matched = 0; i < n && !matched; i++) {
			if (archive_test_acl_match(&acls[marker[i]], type,
			    permset, tag, qual, name)) {
				/* We found a match; remove it. */
				marker[i] = marker[n - 1];
				n--;
				matched = 1;
			}
		}
		if (type == ARCHIVE_ENTRY_ACL_TYPE_ACCESS
		    && tag == ARCHIVE_ENTRY_ACL_USER_OBJ) {
			if (!matched) {
				failure_start(file, line, "No match for "
				    "user_obj perm");
				failure_finish(NULL);
				ret = 1;
			}
			if ((permset << 6) != (mode & 0700)) {
				failure_start(file, line, "USER_OBJ permset "
				    "(%02o) != user mode (%02o)", permset,
				    07 & (mode >> 6));
				failure_finish(NULL);
				ret = 1;
			}
		} else if (type == ARCHIVE_ENTRY_ACL_TYPE_ACCESS
		    && tag == ARCHIVE_ENTRY_ACL_GROUP_OBJ) {
			if (!matched) {
				failure_start(file, line, "No match for "
				    "group_obj perm");
				failure_finish(NULL);
				ret = 1;
			}
			if ((permset << 3) != (mode & 0070)) {
				failure_start(file, line, "GROUP_OBJ permset "
				    "(%02o) != group mode (%02o)", permset,
				    07 & (mode >> 3));
				failure_finish(NULL);
				ret = 1;
			}
		} else if (type == ARCHIVE_ENTRY_ACL_TYPE_ACCESS
		    && tag == ARCHIVE_ENTRY_ACL_OTHER) {
			if (!matched) {
				failure_start(file, line, "No match for "
				    "other perm");
				failure_finish(NULL);
				ret = 1;
			}
			if ((permset << 0) != (mode & 0007)) {
				failure_start(file, line, "OTHER permset "
				    "(%02o) != other mode (%02o)", permset,
				    mode & 07);
				failure_finish(NULL);
				ret = 1;
			}
		} else if (matched != 1) {
			failure_start(file, line, "Could not find match for "
			    "ACL (type=%#010x,permset=%#010x,tag=%d,qual=%d,"
			    "name=``%s'')", type, permset, tag, qual, name);
			failure_finish(NULL);
			ret = 1;
		}
	}
	if (r != ARCHIVE_EOF) {
		failure_start(file, line, "Should not exit before EOF");
		failure_finish(NULL);
		ret = 1;
	}
	if ((want_type & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0 &&
	    (mode_t)(mode & 0777) != (archive_entry_mode(ae) & 0777)) {
		failure_start(file, line, "Mode (%02o) and entry mode (%02o) "
		    "mismatch", mode, archive_entry_mode(ae));
		failure_finish(NULL);
		ret = 1;
	}
	if (n != 0) {
		failure_start(file, line, "Could not find match for ACL "
		    "(type=%#010x,permset=%#010x,tag=%d,qual=%d,name=``%s'')",
		    acls[marker[0]].type, acls[marker[0]].permset,
		    acls[marker[0]].tag, acls[marker[0]].qual,
		    acls[marker[0]].name);
		failure_finish(NULL);
		ret = 1;
		/* Number of ACLs not matched should == 0 */
	}
	free(marker);
	return (ret);
}