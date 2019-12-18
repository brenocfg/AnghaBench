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
struct file {struct cdev_privdata* f_cdevpriv; } ;
struct cdev_privdata {void* cdpd_data; } ;
struct TYPE_2__ {struct file* td_fpop; } ;

/* Variables and functions */
 int EBADF ; 
 int ENOENT ; 
 TYPE_1__* curthread ; 

int
devfs_get_cdevpriv(void **datap)
{
	struct file *fp;
	struct cdev_privdata *p;
	int error;

	fp = curthread->td_fpop;
	if (fp == NULL)
		return (EBADF);
	p = fp->f_cdevpriv;
	if (p != NULL) {
		error = 0;
		*datap = p->cdpd_data;
	} else
		error = ENOENT;
	return (error);
}