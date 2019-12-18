#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct archive_string {int length; int /*<<< orphan*/  s; } ;
struct TYPE_8__ {int keys; scalar_t__ processing; } ;
struct mtree_writer {struct archive_string buf; scalar_t__ classic; scalar_t__ indent; TYPE_3__ set; struct archive_string ebuf; scalar_t__ output_global_set; int /*<<< orphan*/  dironly; } ;
struct TYPE_9__ {unsigned int s; } ;
struct TYPE_10__ {unsigned int s; } ;
struct TYPE_7__ {unsigned int s; } ;
struct TYPE_6__ {unsigned int s; } ;
struct mtree_entry {int nlink; int filetype; int /*<<< orphan*/  reg_info; scalar_t__ size; scalar_t__ rdevminor; scalar_t__ rdevmajor; TYPE_4__ symlink; scalar_t__ devminor; scalar_t__ devmajor; scalar_t__ ino; scalar_t__ uid; scalar_t__ gid; scalar_t__ mode; scalar_t__ mtime_nsec; scalar_t__ mtime; TYPE_5__ fflags_text; TYPE_5__ uname; TYPE_5__ gname; TYPE_2__ basename; TYPE_1__ parentdir; scalar_t__ dir_info; } ;
struct archive_write {struct mtree_writer* format_data; } ;
typedef  unsigned int intmax_t ;

/* Variables and functions */
#define  AE_IFBLK 134 
#define  AE_IFCHR 133 
#define  AE_IFDIR 132 
#define  AE_IFIFO 131 
#define  AE_IFLNK 130 
#define  AE_IFREG 129 
#define  AE_IFSOCK 128 
 int ARCHIVE_OK ; 
 int F_DEV ; 
 int F_FLAGS ; 
 int F_GID ; 
 int F_GNAME ; 
 int F_INO ; 
 int F_MODE ; 
 int F_NLINK ; 
 int F_RESDEV ; 
 int F_SIZE ; 
 int F_SLINK ; 
 int F_TIME ; 
 int F_TYPE ; 
 int F_UID ; 
 int F_UNAME ; 
 int __archive_write_output (struct archive_write*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  archive_strappend_char (struct archive_string*,char) ; 
 int /*<<< orphan*/  archive_strcat (struct archive_string*,char*) ; 
 int /*<<< orphan*/  archive_string_empty (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_sprintf (struct archive_string*,char*,unsigned int,...) ; 
 scalar_t__ archive_strlen (TYPE_5__*) ; 
 int get_global_set_keys (struct mtree_writer*,struct mtree_entry*) ; 
 int /*<<< orphan*/  mtree_indent (struct mtree_writer*) ; 
 int /*<<< orphan*/  mtree_quote (struct archive_string*,unsigned int) ; 
 int /*<<< orphan*/  sum_write (struct archive_string*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_global (struct mtree_writer*) ; 

__attribute__((used)) static int
write_mtree_entry(struct archive_write *a, struct mtree_entry *me)
{
	struct mtree_writer *mtree = a->format_data;
	struct archive_string *str;
	int keys, ret;

	if (me->dir_info) {
		if (mtree->classic) {
			/*
			 * Output a comment line to describe the full
			 * pathname of the entry as mtree utility does
			 * while generating classic format.
			 */
			if (!mtree->dironly)
				archive_strappend_char(&mtree->buf, '\n');
			if (me->parentdir.s)
				archive_string_sprintf(&mtree->buf,
				    "# %s/%s\n",
				    me->parentdir.s, me->basename.s);
			else
				archive_string_sprintf(&mtree->buf,
				    "# %s\n",
				    me->basename.s);
		}
		if (mtree->output_global_set)
			write_global(mtree);
	}
	archive_string_empty(&mtree->ebuf);
	str = (mtree->indent || mtree->classic)? &mtree->ebuf : &mtree->buf;

	if (!mtree->classic && me->parentdir.s) {
		/*
		 * If generating format is not classic one(v1), output
		 * a full pathname.
		 */
		mtree_quote(str, me->parentdir.s);
		archive_strappend_char(str, '/');
	}
	mtree_quote(str, me->basename.s);

	keys = get_global_set_keys(mtree, me);
	if ((keys & F_NLINK) != 0 &&
	    me->nlink != 1 && me->filetype != AE_IFDIR)
		archive_string_sprintf(str, " nlink=%u", me->nlink);

	if ((keys & F_GNAME) != 0 && archive_strlen(&me->gname) > 0) {
		archive_strcat(str, " gname=");
		mtree_quote(str, me->gname.s);
	}
	if ((keys & F_UNAME) != 0 && archive_strlen(&me->uname) > 0) {
		archive_strcat(str, " uname=");
		mtree_quote(str, me->uname.s);
	}
	if ((keys & F_FLAGS) != 0) {
		if (archive_strlen(&me->fflags_text) > 0) {
			archive_strcat(str, " flags=");
			mtree_quote(str, me->fflags_text.s);
		} else if (mtree->set.processing &&
		    (mtree->set.keys & F_FLAGS) != 0)
			/* Overwrite the global parameter. */
			archive_strcat(str, " flags=none");
	}
	if ((keys & F_TIME) != 0)
		archive_string_sprintf(str, " time=%jd.%jd",
		    (intmax_t)me->mtime, (intmax_t)me->mtime_nsec);
	if ((keys & F_MODE) != 0)
		archive_string_sprintf(str, " mode=%o", (unsigned int)me->mode);
	if ((keys & F_GID) != 0)
		archive_string_sprintf(str, " gid=%jd", (intmax_t)me->gid);
	if ((keys & F_UID) != 0)
		archive_string_sprintf(str, " uid=%jd", (intmax_t)me->uid);

	if ((keys & F_INO) != 0)
		archive_string_sprintf(str, " inode=%jd", (intmax_t)me->ino);
	if ((keys & F_RESDEV) != 0) {
		archive_string_sprintf(str,
		    " resdevice=native,%ju,%ju",
		    (uintmax_t)me->devmajor,
		    (uintmax_t)me->devminor);
	}

	switch (me->filetype) {
	case AE_IFLNK:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=link");
		if ((keys & F_SLINK) != 0) {
			archive_strcat(str, " link=");
			mtree_quote(str, me->symlink.s);
		}
		break;
	case AE_IFSOCK:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=socket");
		break;
	case AE_IFCHR:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=char");
		if ((keys & F_DEV) != 0) {
			archive_string_sprintf(str,
			    " device=native,%ju,%ju",
			    (uintmax_t)me->rdevmajor,
			    (uintmax_t)me->rdevminor);
		}
		break;
	case AE_IFBLK:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=block");
		if ((keys & F_DEV) != 0) {
			archive_string_sprintf(str,
			    " device=native,%ju,%ju",
			    (uintmax_t)me->rdevmajor,
			    (uintmax_t)me->rdevminor);
		}
		break;
	case AE_IFDIR:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=dir");
		break;
	case AE_IFIFO:
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=fifo");
		break;
	case AE_IFREG:
	default:	/* Handle unknown file types as regular files. */
		if ((keys & F_TYPE) != 0)
			archive_strcat(str, " type=file");
		if ((keys & F_SIZE) != 0)
			archive_string_sprintf(str, " size=%jd",
			    (intmax_t)me->size);
		break;
	}

	/* Write a bunch of sum. */
	if (me->reg_info)
		sum_write(str, me->reg_info);

	archive_strappend_char(str, '\n');
	if (mtree->indent || mtree->classic)
		mtree_indent(mtree);

	if (mtree->buf.length > 32768) {
		ret = __archive_write_output(
			a, mtree->buf.s, mtree->buf.length);
		archive_string_empty(&mtree->buf);
	} else
		ret = ARCHIVE_OK;
	return (ret);
}