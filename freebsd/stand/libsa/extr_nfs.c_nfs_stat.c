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
typedef  int uint32_t ;
struct stat {int st_mode; void* st_size; void* st_gid; void* st_uid; void* st_nlink; } ;
struct open_file {scalar_t__ f_fsdata; } ;
struct TYPE_3__ {int /*<<< orphan*/ * val; } ;
struct TYPE_4__ {TYPE_1__ fa_size; int /*<<< orphan*/  fa_gid; int /*<<< orphan*/  fa_uid; int /*<<< orphan*/  fa_nlink; int /*<<< orphan*/  fa_mode; int /*<<< orphan*/  fa_type; } ;
struct nfs_iodesc {TYPE_2__ fa; } ;

/* Variables and functions */
 int* nfs_stat_types ; 
 void* ntohl (int /*<<< orphan*/ ) ; 

int
nfs_stat(struct open_file *f, struct stat *sb)
{
	struct nfs_iodesc *fp = (struct nfs_iodesc *)f->f_fsdata;
	uint32_t ftype, mode;

	ftype = ntohl(fp->fa.fa_type);
	mode  = ntohl(fp->fa.fa_mode);
	mode |= nfs_stat_types[ftype & 7];

	sb->st_mode  = mode;
	sb->st_nlink = ntohl(fp->fa.fa_nlink);
	sb->st_uid   = ntohl(fp->fa.fa_uid);
	sb->st_gid   = ntohl(fp->fa.fa_gid);
	sb->st_size  = ntohl(fp->fa.fa_size.val[1]);

	return (0);
}