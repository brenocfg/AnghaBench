#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct statfs {char* f_mntonname; int /*<<< orphan*/  f_fsid; } ;
struct passwd {char* pw_name; } ;
struct TYPE_4__ {int mbo_flags; int mbo_neg; int mbo_uid_min; int mbo_uid_max; int mbo_gid_min; int mbo_gid_max; int mbo_type; int /*<<< orphan*/  mbo_fsid; } ;
struct TYPE_3__ {int mbs_flags; int mbs_neg; int mbs_uid_min; int mbs_uid_max; int mbs_gid_min; int mbs_gid_max; int mbs_prison; } ;
struct mac_bsdextended_rule {int mbr_mode; TYPE_2__ mbr_object; TYPE_1__ mbr_subject; } ;
struct group {char* gr_name; } ;

/* Variables and functions */
 int CHAR_BIT ; 
 int MBI_ADMIN ; 
 int MBI_ALLPERM ; 
 int MBI_EXEC ; 
 int MBI_READ ; 
 int MBI_STAT ; 
 int MBI_WRITE ; 
 int MBO_ALL_FLAGS ; 
 int MBO_ALL_TYPE ; 
 int MBO_FSID_DEFINED ; 
 int MBO_GID_DEFINED ; 
 int MBO_GID_SUBJECT ; 
 int MBO_SGID ; 
 int MBO_SUID ; 
 int MBO_TYPE_BLK ; 
 int MBO_TYPE_CHR ; 
 int MBO_TYPE_DEFINED ; 
 int MBO_TYPE_DIR ; 
 int MBO_TYPE_FIFO ; 
 int MBO_TYPE_LNK ; 
 int MBO_TYPE_REG ; 
 int MBO_TYPE_SOCK ; 
 int MBO_UID_DEFINED ; 
 int MBO_UID_SUBJECT ; 
 int MBS_ALL_FLAGS ; 
 int MBS_PRISON_DEFINED ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 struct group* getgrgid (int) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 struct passwd* getpwuid (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 size_t snprintf (char*,size_t,char*,...) ; 

int
bsde_rule_to_string(struct mac_bsdextended_rule *rule, char *buf, size_t buflen)
{
	struct group *grp;
	struct passwd *pwd;
	struct statfs *mntbuf;
	char *cur, type[sizeof(rule->mbr_object.mbo_type) * CHAR_BIT + 1];
	size_t left, len;
	int anymode, unknownmode, numfs, i, notdone;

	cur = buf;
	left = buflen;

	len = snprintf(cur, left, "subject ");
	if (len < 0 || len > left)
		goto truncated;
	left -= len;
	cur += len;
	if (rule->mbr_subject.mbs_flags) {
		if (rule->mbr_subject.mbs_neg == MBS_ALL_FLAGS) {
			len = snprintf(cur, left, "not ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
			notdone = 1;
		} else {
			notdone = 0;
		}

		if (!notdone && (rule->mbr_subject.mbs_neg & MBO_UID_DEFINED)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_subject.mbs_flags & MBO_UID_DEFINED) {
			pwd = getpwuid(rule->mbr_subject.mbs_uid_min);
			if (pwd != NULL) {
				len = snprintf(cur, left, "uid %s",
				    pwd->pw_name);
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			} else {
				len = snprintf(cur, left, "uid %u",
				    rule->mbr_subject.mbs_uid_min);
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			}
			if (rule->mbr_subject.mbs_uid_min !=
			    rule->mbr_subject.mbs_uid_max) {
				pwd = getpwuid(rule->mbr_subject.mbs_uid_max);
				if (pwd != NULL) {
					len = snprintf(cur, left, ":%s ",
					    pwd->pw_name);
					if (len < 0 || len > left)
						goto truncated;
					left -= len;
					cur += len;
				} else {
					len = snprintf(cur, left, ":%u ",
					    rule->mbr_subject.mbs_uid_max);
					if (len < 0 || len > left)
						goto truncated;
					left -= len;
					cur += len;
				}
			} else {
				len = snprintf(cur, left, " ");
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			}
		}
		if (!notdone && (rule->mbr_subject.mbs_neg & MBO_GID_DEFINED)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_subject.mbs_flags & MBO_GID_DEFINED) {
			grp = getgrgid(rule->mbr_subject.mbs_gid_min);
			if (grp != NULL) {
				len = snprintf(cur, left, "gid %s",
				    grp->gr_name);
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			} else {
				len = snprintf(cur, left, "gid %u",
				    rule->mbr_subject.mbs_gid_min);
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			}
			if (rule->mbr_subject.mbs_gid_min !=
			    rule->mbr_subject.mbs_gid_max) {
				grp = getgrgid(rule->mbr_subject.mbs_gid_max);
				if (grp != NULL) {
					len = snprintf(cur, left, ":%s ",
					    grp->gr_name);
					if (len < 0 || len > left)
						goto truncated;
					left -= len;
					cur += len;
				} else {
					len = snprintf(cur, left, ":%u ",
					    rule->mbr_subject.mbs_gid_max);
					if (len < 0 || len > left)
						goto truncated;
					left -= len;
					cur += len;
				}
			} else {
				len = snprintf(cur, left, " ");
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			}
		}
		if (!notdone && (rule->mbr_subject.mbs_neg & MBS_PRISON_DEFINED)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_subject.mbs_flags & MBS_PRISON_DEFINED) {
			len = snprintf(cur, left, "jailid %d ",
			    rule->mbr_subject.mbs_prison);
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
	}

	len = snprintf(cur, left, "object ");
	if (len < 0 || len > left)
		goto truncated;
	left -= len;
	cur += len;
	if (rule->mbr_object.mbo_flags) {
		if (rule->mbr_object.mbo_neg == MBO_ALL_FLAGS) {
			len = snprintf(cur, left, "not ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
			notdone = 1;
		} else {
			notdone = 0;
		}

		if (!notdone && (rule->mbr_object.mbo_neg & MBO_UID_DEFINED)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_object.mbo_flags & MBO_UID_DEFINED) {
			pwd = getpwuid(rule->mbr_object.mbo_uid_min);
			if (pwd != NULL) {
				len = snprintf(cur, left, "uid %s",
				    pwd->pw_name);
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			} else {
				len = snprintf(cur, left, "uid %u",
				    rule->mbr_object.mbo_uid_min);
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			}
			if (rule->mbr_object.mbo_uid_min !=
			    rule->mbr_object.mbo_uid_max) {
				pwd = getpwuid(rule->mbr_object.mbo_uid_max);
				if (pwd != NULL) {
					len = snprintf(cur, left, ":%s ",
					    pwd->pw_name);
					if (len < 0 || len > left)
						goto truncated;
					left -= len;
					cur += len;
				} else {
					len = snprintf(cur, left, ":%u ",
					    rule->mbr_object.mbo_uid_max);
					if (len < 0 || len > left)
						goto truncated;
					left -= len;
					cur += len;
				}
			} else {
				len = snprintf(cur, left, " ");
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			}
		}
		if (!notdone && (rule->mbr_object.mbo_neg & MBO_GID_DEFINED)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_object.mbo_flags & MBO_GID_DEFINED) {
			grp = getgrgid(rule->mbr_object.mbo_gid_min);
			if (grp != NULL) {
				len = snprintf(cur, left, "gid %s",
				    grp->gr_name);
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			} else {
				len = snprintf(cur, left, "gid %u",
				    rule->mbr_object.mbo_gid_min);
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			}
			if (rule->mbr_object.mbo_gid_min !=
			    rule->mbr_object.mbo_gid_max) {
				grp = getgrgid(rule->mbr_object.mbo_gid_max);
				if (grp != NULL) {
					len = snprintf(cur, left, ":%s ",
					    grp->gr_name);
					if (len < 0 || len > left)
						goto truncated;
					left -= len;
					cur += len;
				} else {
					len = snprintf(cur, left, ":%u ",
					    rule->mbr_object.mbo_gid_max);
					if (len < 0 || len > left)
						goto truncated;
					left -= len;
					cur += len;
				}
			} else {
				len = snprintf(cur, left, " ");
				if (len < 0 || len > left)
					goto truncated;
				left -= len;
				cur += len;
			}
		}
		if (!notdone && (rule->mbr_object.mbo_neg & MBO_FSID_DEFINED)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_object.mbo_flags & MBO_FSID_DEFINED) {
			numfs = getmntinfo(&mntbuf, MNT_NOWAIT);
			for (i = 0; i < numfs; i++)
				if (memcmp(&(rule->mbr_object.mbo_fsid),
				    &(mntbuf[i].f_fsid),
				    sizeof(mntbuf[i].f_fsid)) == 0)
					break;
			len = snprintf(cur, left, "filesys %s ",
			    i == numfs ? "???" : mntbuf[i].f_mntonname);
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (!notdone && (rule->mbr_object.mbo_neg & MBO_SUID)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_object.mbo_flags & MBO_SUID) {
			len = snprintf(cur, left, "suid ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (!notdone && (rule->mbr_object.mbo_neg & MBO_SGID)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_object.mbo_flags & MBO_SGID) {
			len = snprintf(cur, left, "sgid ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (!notdone && (rule->mbr_object.mbo_neg & MBO_UID_SUBJECT)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_object.mbo_flags & MBO_UID_SUBJECT) {
			len = snprintf(cur, left, "uid_of_subject ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (!notdone && (rule->mbr_object.mbo_neg & MBO_GID_SUBJECT)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_object.mbo_flags & MBO_GID_SUBJECT) {
			len = snprintf(cur, left, "gid_of_subject ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (!notdone && (rule->mbr_object.mbo_neg & MBO_TYPE_DEFINED)) {
			len = snprintf(cur, left, "! ");
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
		if (rule->mbr_object.mbo_flags & MBO_TYPE_DEFINED) {
			i = 0;
			if (rule->mbr_object.mbo_type & MBO_TYPE_REG)
				type[i++] = 'r';
			if (rule->mbr_object.mbo_type & MBO_TYPE_DIR)
				type[i++] = 'd';
			if (rule->mbr_object.mbo_type & MBO_TYPE_BLK)
				type[i++] = 'b';
			if (rule->mbr_object.mbo_type & MBO_TYPE_CHR)
				type[i++] = 'c';
			if (rule->mbr_object.mbo_type & MBO_TYPE_LNK)
				type[i++] = 'l';
			if (rule->mbr_object.mbo_type & MBO_TYPE_SOCK)
				type[i++] = 's';
			if (rule->mbr_object.mbo_type & MBO_TYPE_FIFO)
				type[i++] = 'p';
			if (rule->mbr_object.mbo_type == MBO_ALL_TYPE) {
				i = 0;
				type[i++] = 'a';
			}
			type[i++] = '\0';
			len = snprintf(cur, left, "type %s ", type);
			if (len < 0 || len > left)
				goto truncated;
			left -= len;
			cur += len;
		}
	}

	len = snprintf(cur, left, "mode ");
	if (len < 0 || len > left)
		goto truncated;
	left -= len;
	cur += len;

	anymode = (rule->mbr_mode & MBI_ALLPERM);
	unknownmode = (rule->mbr_mode & ~MBI_ALLPERM);

	if (rule->mbr_mode & MBI_ADMIN) {
		len = snprintf(cur, left, "a");
		if (len < 0 || len > left)
			goto truncated;

		left -= len;
		cur += len;
	}
	if (rule->mbr_mode & MBI_READ) {
		len = snprintf(cur, left, "r");
		if (len < 0 || len > left)
			goto truncated;

		left -= len;
		cur += len;
	}
	if (rule->mbr_mode & MBI_STAT) {
		len = snprintf(cur, left, "s");
		if (len < 0 || len > left)
			goto truncated;

		left -= len;
		cur += len;
	}
	if (rule->mbr_mode & MBI_WRITE) {
		len = snprintf(cur, left, "w");
		if (len < 0 || len > left)
			goto truncated;

		left -= len;
		cur += len;
	}
	if (rule->mbr_mode & MBI_EXEC) {
		len = snprintf(cur, left, "x");
		if (len < 0 || len > left)
			goto truncated;

		left -= len;
		cur += len;
	}
	if (!anymode) {
		len = snprintf(cur, left, "n");
		if (len < 0 || len > left)
			goto truncated;

		left -= len;
		cur += len;
	}
	if (unknownmode) {
		len = snprintf(cur, left, "?");
		if (len < 0 || len > left)
			goto truncated;

		left -= len;
		cur += len;
	}

	return (0);

truncated:
	return (-1);
}