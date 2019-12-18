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
typedef  int /*<<< orphan*/  u_long ;
struct open_file {int /*<<< orphan*/ * f_fsdata; } ;
struct nfs_iodesc {int dummy; } ;

/* Variables and functions */
 scalar_t__ debug ; 
 int /*<<< orphan*/  free (struct nfs_iodesc*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

int
nfs_close(struct open_file *f)
{
	struct nfs_iodesc *fp = (struct nfs_iodesc *)f->f_fsdata;

#ifdef NFS_DEBUG
	if (debug)
		printf("nfs_close: fp=0x%lx\n", (u_long)fp);
#endif

	free(fp);
	f->f_fsdata = NULL;

	return (0);
}