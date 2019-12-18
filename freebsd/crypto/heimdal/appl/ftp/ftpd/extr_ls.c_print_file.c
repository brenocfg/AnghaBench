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
struct fileinfo {int link; int /*<<< orphan*/ * filename; int /*<<< orphan*/  date; int /*<<< orphan*/  size; int /*<<< orphan*/ * minor; int /*<<< orphan*/ * major; int /*<<< orphan*/  group; int /*<<< orphan*/  user; int /*<<< orphan*/  n_link; int /*<<< orphan*/  mode; int /*<<< orphan*/  bsize; int /*<<< orphan*/  inode; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LS_INODE ; 
 int LS_SIZE ; 
 int /*<<< orphan*/  sec_fprintf2 (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
print_file(FILE *out,
	   int flags,
	   struct fileinfo *f,
	   int max_inode,
	   int max_bsize,
	   int max_n_link,
	   int max_user,
	   int max_group,
	   int max_size,
	   int max_major,
	   int max_minor,
	   int max_date)
{
    if(f->filename == NULL)
	return;

    if(flags & LS_INODE) {
	sec_fprintf2(out, "%*d", max_inode, f->inode);
	sec_fprintf2(out, "  ");
    }
    if(flags & LS_SIZE) {
	sec_fprintf2(out, "%*d", max_bsize, f->bsize);
	sec_fprintf2(out, "  ");
    }
    sec_fprintf2(out, "%s", f->mode);
    sec_fprintf2(out, "  ");
    sec_fprintf2(out, "%*d", max_n_link, f->n_link);
    sec_fprintf2(out, " ");
    sec_fprintf2(out, "%-*s", max_user, f->user);
    sec_fprintf2(out, "  ");
    sec_fprintf2(out, "%-*s", max_group, f->group);
    sec_fprintf2(out, "  ");
    if(f->major != NULL && f->minor != NULL)
	sec_fprintf2(out, "%*s, %*s", max_major, f->major, max_minor, f->minor);
    else
	sec_fprintf2(out, "%*s", max_size, f->size);
    sec_fprintf2(out, " ");
    sec_fprintf2(out, "%*s", max_date, f->date);
    sec_fprintf2(out, " ");
    sec_fprintf2(out, "%s", f->filename);
    if(f->link)
	sec_fprintf2(out, " -> %s", f->link);
    sec_fprintf2(out, "\r\n");
}