#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_18__ {char header_size; unsigned char log2_bs; int uncompressed_size; } ;
struct TYPE_16__ {char* s; } ;
struct TYPE_11__ {char* s; size_t length; } ;
struct isofile {TYPE_9__ zisofs; int /*<<< orphan*/  entry; TYPE_7__ symlink; TYPE_6__* cur_content; TYPE_5__* hardlink_target; TYPE_2__ basename; } ;
struct isoent {int dir_location; struct isoent* parent; TYPE_8__* rr_child; scalar_t__ dir; struct isofile* file; scalar_t__ virtual; struct isoent* rr_parent; } ;
struct TYPE_12__ {scalar_t__ rr; } ;
struct TYPE_10__ {struct isoent* rootent; } ;
struct iso9660 {int /*<<< orphan*/  location_rrip_er; TYPE_3__ opt; TYPE_1__ primary; } ;
struct ctl_extr_rec {int dr_len; } ;
typedef  int mode_t ;
typedef  scalar_t__ int64_t ;
typedef  enum dir_rec_type { ____Placeholder_dir_rec_type } dir_rec_type ;
struct TYPE_17__ {int dir_location; } ;
struct TYPE_15__ {int location; } ;
struct TYPE_14__ {TYPE_4__* cur_content; } ;
struct TYPE_13__ {int location; } ;

/* Variables and functions */
 scalar_t__ AE_IFBLK ; 
 scalar_t__ AE_IFCHR ; 
 scalar_t__ AE_IFLNK ; 
 int DIR_REC_NORMAL ; 
 int DIR_REC_PARENT ; 
 int DIR_REC_SELF ; 
 scalar_t__ OPT_RR_USEFUL ; 
 int /*<<< orphan*/  RRIP_ER_SIZE ; 
 int RR_CE_SIZE ; 
 unsigned char RR_USE_CL ; 
 unsigned char RR_USE_NM ; 
 unsigned char RR_USE_PL ; 
 unsigned char RR_USE_PN ; 
 unsigned char RR_USE_PX ; 
 unsigned char RR_USE_RE ; 
 unsigned char RR_USE_SL ; 
 unsigned char RR_USE_TF ; 
 unsigned char TF_ACCESS ; 
 unsigned char TF_ATTRIBUTES ; 
 unsigned char TF_CREATION ; 
 unsigned char TF_MODIFY ; 
 scalar_t__ archive_entry_atime (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_atime_is_set (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_birthtime (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_birthtime_is_set (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_ctime (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_ctime_is_set (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_filetype (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_gid (int /*<<< orphan*/ ) ; 
 int archive_entry_mode (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_mtime (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_mtime_is_set (int /*<<< orphan*/ ) ; 
 int archive_entry_nlink (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_rdev (int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_uid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extra_close_record (struct ctl_extr_rec*,int /*<<< orphan*/ ) ; 
 unsigned char* extra_next_record (struct ctl_extr_rec*,int) ; 
 unsigned char* extra_open_record (unsigned char*,int,struct isoent*,struct ctl_extr_rec*) ; 
 int extra_space (struct ctl_extr_rec*) ; 
 int /*<<< orphan*/  extra_tell_used_size (struct ctl_extr_rec*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 int /*<<< orphan*/  set_SUSP_CE (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_num_733 (unsigned char*,int) ; 
 int /*<<< orphan*/  set_time_915 (unsigned char*,scalar_t__) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
set_directory_record_rr(unsigned char *bp, int dr_len,
    struct isoent *isoent, struct iso9660 *iso9660, enum dir_rec_type t)
{
	/* Flags(BP 5) of the Rockridge "RR" System Use Field */
	unsigned char rr_flag;
#define RR_USE_PX	0x01
#define RR_USE_PN	0x02
#define RR_USE_SL	0x04
#define RR_USE_NM	0x08
#define RR_USE_CL	0x10
#define RR_USE_PL	0x20
#define RR_USE_RE	0x40
#define RR_USE_TF	0x80
	int length;
	struct ctl_extr_rec ctl;
	struct isoent *rr_parent, *pxent;
	struct isofile *file;

	bp = extra_open_record(bp, dr_len, isoent, &ctl);

	if (t == DIR_REC_PARENT) {
		rr_parent = isoent->rr_parent;
		pxent = isoent->parent;
		if (rr_parent != NULL)
			isoent = rr_parent;
		else
			isoent = isoent->parent;
	} else {
		rr_parent = NULL;
		pxent = isoent;
	}
	file = isoent->file;

	if (t != DIR_REC_NORMAL) {
		rr_flag = RR_USE_PX | RR_USE_TF;
		if (rr_parent != NULL)
			rr_flag |= RR_USE_PL;
	} else {
		rr_flag = RR_USE_PX | RR_USE_NM | RR_USE_TF;
		if (archive_entry_filetype(file->entry) == AE_IFLNK)
			rr_flag |= RR_USE_SL;
		if (isoent->rr_parent != NULL)
			rr_flag |= RR_USE_RE;
		if (isoent->rr_child != NULL)
			rr_flag |= RR_USE_CL;
		if (archive_entry_filetype(file->entry) == AE_IFCHR ||
		    archive_entry_filetype(file->entry) == AE_IFBLK)
			rr_flag |= RR_USE_PN;
#ifdef COMPAT_MKISOFS
		/*
		 * mkisofs 2.01.01a63 records "RE" extension to
		 * the entry of "rr_moved" directory.
		 * I don't understand this behavior.
		 */
		if (isoent->virtual &&
		    isoent->parent == iso9660->primary.rootent &&
		    strcmp(isoent->file->basename.s, "rr_moved") == 0)
			rr_flag |= RR_USE_RE;
#endif
	}

	/* Write "SP" System Use Entry. */
	if (t == DIR_REC_SELF && isoent == isoent->parent) {
		length = 7;
		if (bp != NULL) {
			bp[1] = 'S';
			bp[2] = 'P';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			bp[5] = 0xBE;  /* Check Byte	*/
			bp[6] = 0xEF;  /* Check Byte	*/
			bp[7] = 0;
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "RR" System Use Entry. */
	length = 5;
	if (extra_space(&ctl) < length)
		bp = extra_next_record(&ctl, length);
	if (bp != NULL) {
		bp[1] = 'R';
		bp[2] = 'R';
		bp[3] = length;
		bp[4] = 1;	/* version */
		bp[5] = rr_flag;
		bp += length;
	}
	extra_tell_used_size(&ctl, length);

	/* Write "NM" System Use Entry. */
	if (rr_flag & RR_USE_NM) {
		/*
		 *   "NM" Format:
		 *     e.g. a basename is 'foo'
		 *               len  ver  flg
		 *    +----+----+----+----+----+----+----+----+
		 *    | 'N'| 'M'| 08 | 01 | 00 | 'f'| 'o'| 'o'|
		 *    +----+----+----+----+----+----+----+----+
		 *    <----------------- len ----------------->
		 */
		size_t nmlen = file->basename.length;
		const char *nm = file->basename.s;
		size_t nmmax;

		if (extra_space(&ctl) < 6)
			bp = extra_next_record(&ctl, 6);
		if (bp != NULL) {
			bp[1] = 'N';
			bp[2] = 'M';
			bp[4] = 1;	    /* version	*/
		}
		nmmax = extra_space(&ctl);
		if (nmmax > 0xff)
			nmmax = 0xff;
		while (nmlen + 5 > nmmax) {
			length = (int)nmmax;
			if (bp != NULL) {
				bp[3] = length;
				bp[5] = 0x01;/* Alternate Name continues
					       * in next "NM" field */
				memcpy(bp+6, nm, length - 5);
				bp += length;
			}
			nmlen -= length - 5;
			nm += length - 5;
			extra_tell_used_size(&ctl, length);
			if (extra_space(&ctl) < 6) {
				bp = extra_next_record(&ctl, 6);
				nmmax = extra_space(&ctl);
				if (nmmax > 0xff)
					nmmax = 0xff;
			}
			if (bp != NULL) {
				bp[1] = 'N';
				bp[2] = 'M';
				bp[4] = 1;    /* version */
			}
		}
		length = 5 + (int)nmlen;
		if (bp != NULL) {
			bp[3] = length;
			bp[5] = 0;
			memcpy(bp+6, nm, nmlen);
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "PX" System Use Entry. */
	if (rr_flag & RR_USE_PX) {
		/*
		 *   "PX" Format:
		 *               len  ver
		 *    +----+----+----+----+-----------+-----------+
		 *    | 'P'| 'X'| 2C | 01 | FILE MODE |   LINKS   |
		 *    +----+----+----+----+-----------+-----------+
		 *    0    1    2    3    4          12          20
		 *    +-----------+-----------+------------------+
		 *    |  USER ID  | GROUP ID  |FILE SERIAL NUMBER|
		 *    +-----------+-----------+------------------+
		 *   20          28          36                 44
		 */
		length = 44;
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			mode_t mode;
			int64_t uid;
			int64_t gid;

			mode = archive_entry_mode(file->entry);
			uid = archive_entry_uid(file->entry);
			gid = archive_entry_gid(file->entry);
			if (iso9660->opt.rr == OPT_RR_USEFUL) {
				/*
				 * This action is similar to mkisofs -r option
				 * but our rockridge=useful option does not
				 * set a zero to uid and gid.
				 */
				/* set all read bit ON */
				mode |= 0444;
#if !defined(_WIN32) && !defined(__CYGWIN__)
				if (mode & 0111)
#endif
					/* set all exec bit ON */
					mode |= 0111;
				/* clear all write bits. */
				mode &= ~0222;
				/* clear setuid,setgid,sticky bits. */
				mode &= ~07000;
			}

			bp[1] = 'P';
			bp[2] = 'X';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			/* file mode */
			set_num_733(bp+5, mode);
			/* file links (stat.st_nlink) */
			set_num_733(bp+13,
			    archive_entry_nlink(file->entry));
			set_num_733(bp+21, (uint32_t)uid);
			set_num_733(bp+29, (uint32_t)gid);
			/* File Serial Number */
			if (pxent->dir)
				set_num_733(bp+37, pxent->dir_location);
			else if (file->hardlink_target != NULL)
				set_num_733(bp+37,
				    file->hardlink_target->cur_content->location);
			else
				set_num_733(bp+37,
				    file->cur_content->location);
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "SL" System Use Entry. */
	if (rr_flag & RR_USE_SL) {
		/*
		 *   "SL" Format:
		 *     e.g. a symbolic name is 'foo/bar'
		 *               len  ver  flg
		 *    +----+----+----+----+----+------------+
		 *    | 'S'| 'L'| 0F | 01 | 00 | components |
		 *    +----+----+----+----+----+-----+------+
		 *    0    1    2    3    4    5  ...|...  15
		 *    <----------------- len --------+------>
		 *    components :                   |
		 *     cflg clen                     |
		 *    +----+----+----+----+----+     |
		 *    | 00 | 03 | 'f'| 'o'| 'o'| <---+
		 *    +----+----+----+----+----+     |
		 *    5    6    7    8    9   10     |
		 *     cflg clen                     |
		 *    +----+----+----+----+----+     |
		 *    | 00 | 03 | 'b'| 'a'| 'r'| <---+
		 *    +----+----+----+----+----+
		 *   10   11   12   13   14   15
		 *
		 *    - cflg : flag of component
		 *    - clen : length of component
		 */
		const char *sl;
		char sl_last;

		if (extra_space(&ctl) < 7)
			bp = extra_next_record(&ctl, 7);
		sl = file->symlink.s;
		sl_last = '\0';
		if (bp != NULL) {
			bp[1] = 'S';
			bp[2] = 'L';
			bp[4] = 1;	/* version	*/
		}
		for (;;) {
			unsigned char *nc, *cf,  *cl, cldmy = 0;
			int sllen, slmax;

			slmax = extra_space(&ctl);
			if (slmax > 0xff)
				slmax = 0xff;
			if (bp != NULL)
				nc = &bp[6];
			else
				nc = NULL;
			cf = cl = NULL;
			sllen = 0;
			while (*sl && sllen + 11 < slmax) {
				if (sl_last == '\0' && sl[0] == '/') {
					/*
					 *     flg  len
					 *    +----+----+
					 *    | 08 | 00 | ROOT component.
					 *    +----+----+ ("/")
					 *
				 	 * Root component has to appear
				 	 * at the first component only.
					 */
					if (nc != NULL) {
						cf = nc++;
						*cf = 0x08; /* ROOT */
						*nc++ = 0;
					}
					sllen += 2;
					sl++;
					sl_last = '/';
					cl = NULL;
					continue;
				}
				if (((sl_last == '\0' || sl_last == '/') &&
				      sl[0] == '.' && sl[1] == '.' &&
				     (sl[2] == '/' || sl[2] == '\0')) ||
				    (sl[0] == '/' &&
				      sl[1] == '.' && sl[2] == '.' &&
				     (sl[3] == '/' || sl[3] == '\0'))) {
					/*
					 *     flg  len
					 *    +----+----+
					 *    | 04 | 00 | PARENT component.
					 *    +----+----+ ("..")
					 */
					if (nc != NULL) {
						cf = nc++;
						*cf = 0x04; /* PARENT */
						*nc++ = 0;
					}
					sllen += 2;
					if (sl[0] == '/')
						sl += 3;/* skip "/.." */
					else
						sl += 2;/* skip ".." */
					sl_last = '.';
					cl = NULL;
					continue;
				}
				if (((sl_last == '\0' || sl_last == '/') &&
				      sl[0] == '.' &&
				     (sl[1] == '/' || sl[1] == '\0')) ||
				    (sl[0] == '/' && sl[1] == '.' &&
				     (sl[2] == '/' || sl[2] == '\0'))) {
					/*
					 *     flg  len
					 *    +----+----+
					 *    | 02 | 00 | CURRENT component.
					 *    +----+----+ (".")
					 */
					if (nc != NULL) {
						cf = nc++;
						*cf = 0x02; /* CURRENT */
						*nc++ = 0;
					}
					sllen += 2;
					if (sl[0] == '/')
						sl += 2;/* skip "/." */
					else
						sl ++;  /* skip "." */
					sl_last = '.';
					cl = NULL;
					continue;
				}
				if (sl[0] == '/' || cl == NULL) {
					if (nc != NULL) {
						cf = nc++;
						*cf = 0;
						cl = nc++;
						*cl = 0;
					} else
						cl = &cldmy;
					sllen += 2;
					if (sl[0] == '/') {
						sl_last = *sl++;
						continue;
					}
				}
				sl_last = *sl++;
				if (nc != NULL) {
					*nc++ = sl_last;
					(*cl) ++;
				}
				sllen++;
			}
			if (*sl) {
				length = 5 + sllen;
				if (bp != NULL) {
					/*
					 * Mark flg as CONTINUE component.
					 */
					*cf |= 0x01;
					/*
					 *               len  ver  flg
					 *    +----+----+----+----+----+-
					 *    | 'S'| 'L'| XX | 01 | 01 |
					 *    +----+----+----+----+----+-
					 *                           ^
					 *           continues in next "SL"
					 */
					bp[3] = length;
					bp[5] = 0x01;/* This Symbolic Link
						      * continues in next
						      * "SL" field */
					bp += length;
				}
				extra_tell_used_size(&ctl, length);
				if (extra_space(&ctl) < 11)
					bp = extra_next_record(&ctl, 11);
				if (bp != NULL) {
					/* Next 'SL' */
					bp[1] = 'S';
					bp[2] = 'L';
					bp[4] = 1;    /* version */
				}
			} else {
				length = 5 + sllen;
				if (bp != NULL) {
					bp[3] = length;
					bp[5] = 0;
					bp += length;
				}
				extra_tell_used_size(&ctl, length);
				break;
			}
		}
	}

	/* Write "TF" System Use Entry. */
	if (rr_flag & RR_USE_TF) {
		/*
		 *   "TF" Format:
		 *               len  ver
		 *    +----+----+----+----+-----+-------------+
		 *    | 'T'| 'F'| XX | 01 |FLAGS| TIME STAMPS |
		 *    +----+----+----+----+-----+-------------+
		 *    0    1    2    3    4     5            XX
		 *    TIME STAMPS : ISO 9660 Standard 9.1.5.
		 *                  If TF_LONG_FORM FLAGS is set,
		 *                  use ISO9660 Standard 8.4.26.1.
		 */
#define TF_CREATION	0x01	/* Creation time recorded		*/
#define TF_MODIFY	0x02	/* Modification time recorded		*/
#define TF_ACCESS	0x04	/* Last Access time recorded		*/
#define TF_ATTRIBUTES	0x08	/* Last Attribute Change time recorded  */
#define TF_BACKUP	0x10	/* Last Backup time recorded		*/
#define TF_EXPIRATION	0x20	/* Expiration time recorded		*/
#define TF_EFFECTIVE	0x40	/* Effective time recorded		*/
#define TF_LONG_FORM	0x80	/* ISO 9660 17-byte time format used	*/
		unsigned char tf_flags;

		length = 5;
		tf_flags = 0;
#ifndef COMPAT_MKISOFS
		if (archive_entry_birthtime_is_set(file->entry) &&
		    archive_entry_birthtime(file->entry) <=
		    archive_entry_mtime(file->entry)) {
			length += 7;
			tf_flags |= TF_CREATION;
		}
#endif
		if (archive_entry_mtime_is_set(file->entry)) {
			length += 7;
			tf_flags |= TF_MODIFY;
		}
		if (archive_entry_atime_is_set(file->entry)) {
			length += 7;
			tf_flags |= TF_ACCESS;
		}
		if (archive_entry_ctime_is_set(file->entry)) {
			length += 7;
			tf_flags |= TF_ATTRIBUTES;
		}
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			bp[1] = 'T';
			bp[2] = 'F';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			bp[5] = tf_flags;
			bp += 5;
			/* Creation time */
			if (tf_flags & TF_CREATION) {
				set_time_915(bp+1,
				    archive_entry_birthtime(file->entry));
				bp += 7;
			}
			/* Modification time */
			if (tf_flags & TF_MODIFY) {
				set_time_915(bp+1,
				    archive_entry_mtime(file->entry));
				bp += 7;
			}
			/* Last Access time */
			if (tf_flags & TF_ACCESS) {
				set_time_915(bp+1,
				    archive_entry_atime(file->entry));
				bp += 7;
			}
			/* Last Attribute Change time */
			if (tf_flags & TF_ATTRIBUTES) {
				set_time_915(bp+1,
				    archive_entry_ctime(file->entry));
				bp += 7;
			}
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "RE" System Use Entry. */
	if (rr_flag & RR_USE_RE) {
		/*
		 *   "RE" Format:
		 *               len  ver
		 *    +----+----+----+----+
		 *    | 'R'| 'E'| 04 | 01 |
		 *    +----+----+----+----+
		 *    0    1    2    3    4
		 */
		length = 4;
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			bp[1] = 'R';
			bp[2] = 'E';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "PL" System Use Entry. */
	if (rr_flag & RR_USE_PL) {
		/*
		 *   "PL" Format:
		 *               len  ver
		 *    +----+----+----+----+------------+
		 *    | 'P'| 'L'| 0C | 01 | *LOCATION  |
		 *    +----+----+----+----+------------+
		 *    0    1    2    3    4           12
		 *    *LOCATION: location of parent directory
		 */
		length = 12;
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			bp[1] = 'P';
			bp[2] = 'L';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			set_num_733(bp + 5,
			    rr_parent->dir_location);
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "CL" System Use Entry. */
	if (rr_flag & RR_USE_CL) {
		/*
		 *   "CL" Format:
		 *               len  ver
		 *    +----+----+----+----+------------+
		 *    | 'C'| 'L'| 0C | 01 | *LOCATION  |
		 *    +----+----+----+----+------------+
		 *    0    1    2    3    4           12
		 *    *LOCATION: location of child directory
		 */
		length = 12;
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			bp[1] = 'C';
			bp[2] = 'L';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			set_num_733(bp + 5,
			    isoent->rr_child->dir_location);
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "PN" System Use Entry. */
	if (rr_flag & RR_USE_PN) {
		/*
		 *   "PN" Format:
		 *               len  ver
		 *    +----+----+----+----+------------+------------+
		 *    | 'P'| 'N'| 14 | 01 | dev_t high | dev_t low  |
		 *    +----+----+----+----+------------+------------+
		 *    0    1    2    3    4           12           20
		 */
		length = 20;
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			uint64_t dev;

			bp[1] = 'P';
			bp[2] = 'N';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			dev = (uint64_t)archive_entry_rdev(file->entry);
			set_num_733(bp + 5, (uint32_t)(dev >> 32));
			set_num_733(bp + 13, (uint32_t)(dev & 0xFFFFFFFF));
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "ZF" System Use Entry. */
	if (file->zisofs.header_size) {
		/*
		 *   "ZF" Format:
		 *               len  ver
		 *    +----+----+----+----+----+----+-------------+
		 *    | 'Z'| 'F'| 10 | 01 | 'p'| 'z'| Header Size |
		 *    +----+----+----+----+----+----+-------------+
		 *    0    1    2    3    4    5    6             7
		 *    +--------------------+-------------------+
		 *    | Log2 of block Size | Uncompressed Size |
		 *    +--------------------+-------------------+
		 *    7                    8                   16
		 */
		length = 16;
		if (extra_space(&ctl) < length)
			bp = extra_next_record(&ctl, length);
		if (bp != NULL) {
			bp[1] = 'Z';
			bp[2] = 'F';
			bp[3] = length;
			bp[4] = 1;	/* version	*/
			bp[5] = 'p';
			bp[6] = 'z';
			bp[7] = file->zisofs.header_size;
			bp[8] = file->zisofs.log2_bs;
			set_num_733(bp + 9, file->zisofs.uncompressed_size);
			bp += length;
		}
		extra_tell_used_size(&ctl, length);
	}

	/* Write "CE" System Use Entry. */
	if (t == DIR_REC_SELF && isoent == isoent->parent) {
		length = RR_CE_SIZE;
		if (bp != NULL)
			set_SUSP_CE(bp+1, iso9660->location_rrip_er,
			    0, RRIP_ER_SIZE);
		extra_tell_used_size(&ctl, length);
	}

	extra_close_record(&ctl, 0);

	return (ctl.dr_len);
}