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
typedef  void* uid_t ;
struct fsid {int dummy; } ;
struct mac_bsdextended_object {int mbo_flags; int mbo_neg; int mbo_type; struct fsid mbo_fsid; void* mbo_gid_max; void* mbo_gid_min; void* mbo_uid_max; void* mbo_uid_min; } ;
typedef  void* gid_t ;

/* Variables and functions */
 int MBO_ALL_FLAGS ; 
 int MBO_FSID_DEFINED ; 
 int MBO_GID_DEFINED ; 
 int MBO_GID_SUBJECT ; 
 int MBO_SGID ; 
 int MBO_SUID ; 
 int MBO_TYPE_DEFINED ; 
 int MBO_UID_DEFINED ; 
 int MBO_UID_SUBJECT ; 
 scalar_t__ bsde_parse_fsid (char*,struct fsid*,size_t,char*) ; 
 scalar_t__ bsde_parse_gidrange (char*,void**,void**,size_t,char*) ; 
 scalar_t__ bsde_parse_type (char*,int*,size_t,char*) ; 
 scalar_t__ bsde_parse_uidrange (char*,void**,void**,size_t,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
bsde_parse_object(int argc, char *argv[],
    struct mac_bsdextended_object *object, size_t buflen, char *errstr)
{
	int not_seen, flags;
	int current, neg, nextnot;
	int type;
	uid_t uid_min, uid_max;
	gid_t gid_min, gid_max;
	struct fsid fsid;

	current = 0;
	flags = 0;
	neg = 0;
	nextnot = 0;
	type = 0;

	if (strcmp("not", argv[current]) == 0) {
		not_seen = 1;
		current++;
	} else
		not_seen = 0;

	while (current < argc) {
		if (strcmp(argv[current], "uid") == 0) {
			if (current + 2 > argc) {
				snprintf(errstr, buflen, "uid short");
				return (-1);
			}
			if (flags & MBO_UID_DEFINED) {
				snprintf(errstr, buflen, "one uid only");
				return (-1);
			}
			if (bsde_parse_uidrange(argv[current+1],
			    &uid_min, &uid_max, buflen, errstr) < 0)
				return (-1);
			flags |= MBO_UID_DEFINED;
			if (nextnot) {
				neg ^= MBO_UID_DEFINED;
				nextnot = 0;
			}
			current += 2;
		} else if (strcmp(argv[current], "gid") == 0) {
			if (current + 2 > argc) {
				snprintf(errstr, buflen, "gid short");
				return (-1);
			}
			if (flags & MBO_GID_DEFINED) {
				snprintf(errstr, buflen, "one gid only");
				return (-1);
			}
			if (bsde_parse_gidrange(argv[current+1],
			    &gid_min, &gid_max, buflen, errstr) < 0)
				return (-1);
			flags |= MBO_GID_DEFINED;
			if (nextnot) {
				neg ^= MBO_GID_DEFINED;
				nextnot = 0;
			}
			current += 2;
		} else if (strcmp(argv[current], "filesys") == 0) {
			if (current + 2 > argc) {
				snprintf(errstr, buflen, "filesys short");
				return (-1);
			}
			if (flags & MBO_FSID_DEFINED) {
				snprintf(errstr, buflen, "one fsid only");
				return (-1);
			}
			if (bsde_parse_fsid(argv[current+1], &fsid,
			    buflen, errstr) < 0)
				return (-1);
			flags |= MBO_FSID_DEFINED;
			if (nextnot) {
				neg ^= MBO_FSID_DEFINED;
				nextnot = 0;
			}
			current += 2;
		} else if (strcmp(argv[current], "suid") == 0) {
			flags |= MBO_SUID;
			if (nextnot) {
				neg ^= MBO_SUID;
				nextnot = 0;
			}
			current += 1;
		} else if (strcmp(argv[current], "sgid") == 0) {
			flags |= MBO_SGID;
			if (nextnot) {
				neg ^= MBO_SGID;
				nextnot = 0;
			}
			current += 1;
		} else if (strcmp(argv[current], "uid_of_subject") == 0) {
			flags |= MBO_UID_SUBJECT;
			if (nextnot) {
				neg ^= MBO_UID_SUBJECT;
				nextnot = 0;
			}
			current += 1;
		} else if (strcmp(argv[current], "gid_of_subject") == 0) {
			flags |= MBO_GID_SUBJECT;
			if (nextnot) {
				neg ^= MBO_GID_SUBJECT;
				nextnot = 0;
			}
			current += 1;
		} else if (strcmp(argv[current], "type") == 0) {
			if (current + 2 > argc) {
				snprintf(errstr, buflen, "type short");
				return (-1);
			}
			if (flags & MBO_TYPE_DEFINED) {
				snprintf(errstr, buflen, "one type only");
				return (-1);
			}
			if (bsde_parse_type(argv[current+1], &type,
			    buflen, errstr) < 0)
				return (-1);
			flags |= MBO_TYPE_DEFINED;
			if (nextnot) {
				neg ^= MBO_TYPE_DEFINED;
				nextnot = 0;
			}
			current += 2;
		} else if (strcmp(argv[current], "!") == 0) {
			if (nextnot) {
				snprintf(errstr, buflen,
				    "double negative'");
				return (-1);
			}
			nextnot = 1;
			current += 1;
		} else {
			snprintf(errstr, buflen, "'%s' not expected",
			    argv[current]);
			return (-1);
		}
	}

	object->mbo_flags = flags;
	if (not_seen)
		object->mbo_neg = MBO_ALL_FLAGS ^ neg;
	else
		object->mbo_neg = neg;
	if (flags & MBO_UID_DEFINED) {
		object->mbo_uid_min = uid_min;
		object->mbo_uid_max = uid_max;
	}
	if (flags & MBO_GID_DEFINED) {
		object->mbo_gid_min = gid_min;
		object->mbo_gid_max = gid_max;
	}
	if (flags & MBO_FSID_DEFINED)
		object->mbo_fsid = fsid;
	if (flags & MBO_TYPE_DEFINED)
		object->mbo_type = type;

	return (0);
}