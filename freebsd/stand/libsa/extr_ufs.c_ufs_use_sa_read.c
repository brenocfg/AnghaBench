#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct open_file {int /*<<< orphan*/  f_devdata; TYPE_1__* f_dev; } ;
typedef  int off_t ;
struct TYPE_2__ {int (* dv_strategy ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,void*,size_t*) ;} ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int EIO ; 
 int ENOSPC ; 
 int /*<<< orphan*/  F_READ ; 
 void* malloc (int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,void*,size_t*) ; 

__attribute__((used)) static int
ufs_use_sa_read(void *devfd, off_t loc, void **bufp, int size)
{
	struct open_file *f;
	size_t buf_size;
	int error;

	f = (struct open_file *)devfd;
	if ((*bufp = malloc(size)) == NULL)
		return (ENOSPC);
	error = (f->f_dev->dv_strategy)(f->f_devdata, F_READ, loc / DEV_BSIZE,
	    size, *bufp, &buf_size);
	if (error != 0)
		return (error);
	if (buf_size != size)
		return (EIO);
	return (0);
}