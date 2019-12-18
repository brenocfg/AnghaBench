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
struct mac_bsdextended_subject {int mbs_flags; int mbs_neg; int mbs_prison; void* mbs_gid_max; void* mbs_gid_min; void* mbs_uid_max; void* mbs_uid_min; } ;
typedef  void* gid_t ;

/* Variables and functions */
 int MBS_ALL_FLAGS ; 
 int MBS_GID_DEFINED ; 
 int MBS_PRISON_DEFINED ; 
 int MBS_UID_DEFINED ; 
 int bsde_get_jailid (char*,size_t,char*) ; 
 scalar_t__ bsde_parse_gidrange (char*,void**,void**,size_t,char*) ; 
 scalar_t__ bsde_parse_uidrange (char*,void**,void**,size_t,char*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
bsde_parse_subject(int argc, char *argv[],
    struct mac_bsdextended_subject *subject, size_t buflen, char *errstr)
{
	int not_seen, flags;
	int current, neg, nextnot;
	uid_t uid_min, uid_max;
	gid_t gid_min, gid_max;
	int jid = 0;

	current = 0;
	flags = 0;
	neg = 0;
	nextnot = 0;

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
			if (flags & MBS_UID_DEFINED) {
				snprintf(errstr, buflen, "one uid only");
				return (-1);
			}
			if (bsde_parse_uidrange(argv[current+1],
			    &uid_min, &uid_max, buflen, errstr) < 0)
				return (-1);
			flags |= MBS_UID_DEFINED;
			if (nextnot) {
				neg ^= MBS_UID_DEFINED;
				nextnot = 0;
			}
			current += 2;
		} else if (strcmp(argv[current], "gid") == 0) {
			if (current + 2 > argc) {
				snprintf(errstr, buflen, "gid short");
				return (-1);
			}
			if (flags & MBS_GID_DEFINED) {
				snprintf(errstr, buflen, "one gid only");
				return (-1);
			}
			if (bsde_parse_gidrange(argv[current+1],
			    &gid_min, &gid_max, buflen, errstr) < 0)
				return (-1);
			flags |= MBS_GID_DEFINED;
			if (nextnot) {
				neg ^= MBS_GID_DEFINED;
				nextnot = 0;
			}
			current += 2;
		} else if (strcmp(argv[current], "jailid") == 0) {
			if (current + 2 > argc) {
				snprintf(errstr, buflen, "prison short");
				return (-1);
			}
			if (flags & MBS_PRISON_DEFINED) {
				snprintf(errstr, buflen, "one jail only");
				return (-1);
			}
			jid = bsde_get_jailid(argv[current+1], buflen, errstr);
			if (jid < 0)
				return (-1);
			flags |= MBS_PRISON_DEFINED;
			if (nextnot) {
				neg ^= MBS_PRISON_DEFINED;
				nextnot = 0;
			}
			current += 2;
		} else if (strcmp(argv[current], "!") == 0) {
			if (nextnot) {
				snprintf(errstr, buflen, "double negative");
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

	subject->mbs_flags = flags;
	if (not_seen)
		subject->mbs_neg = MBS_ALL_FLAGS ^ neg;
	else
		subject->mbs_neg = neg;
	if (flags & MBS_UID_DEFINED) {
		subject->mbs_uid_min = uid_min;
		subject->mbs_uid_max = uid_max;
	}
	if (flags & MBS_GID_DEFINED) {
		subject->mbs_gid_min = gid_min;
		subject->mbs_gid_max = gid_max;
	}
	if (flags & MBS_PRISON_DEFINED)
		subject->mbs_prison = jid;

	return (0);
}