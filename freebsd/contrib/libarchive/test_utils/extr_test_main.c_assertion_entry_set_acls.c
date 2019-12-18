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
struct archive_test_acl_t {int /*<<< orphan*/  name; int /*<<< orphan*/  qual; int /*<<< orphan*/  tag; int /*<<< orphan*/  permset; int /*<<< orphan*/  type; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int archive_entry_acl_add_entry (struct archive_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_acl_clear (struct archive_entry*) ; 
 int /*<<< orphan*/  assertion_count (char const*,int) ; 
 int /*<<< orphan*/  failure_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failure_start (char const*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
assertion_entry_set_acls(const char *file, int line, struct archive_entry *ae,
    struct archive_test_acl_t *acls, int n)
{
	int i, r, ret;

	assertion_count(file, line);

	ret = 0;
	archive_entry_acl_clear(ae);
	for (i = 0; i < n; i++) {
		r = archive_entry_acl_add_entry(ae,
		    acls[i].type, acls[i].permset, acls[i].tag,
		    acls[i].qual, acls[i].name);
		if (r != 0) {
			ret = 1;
			failure_start(file, line, "type=%#010x, ",
			    "permset=%#010x, tag=%d, qual=%d name=%s",
			    acls[i].type, acls[i].permset, acls[i].tag,
			    acls[i].qual, acls[i].name);
			failure_finish(NULL);
		}
	}

	return (ret);
}