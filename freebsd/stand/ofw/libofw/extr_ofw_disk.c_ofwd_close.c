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
struct open_file {struct ofw_devdesc* f_devdata; } ;
struct ofw_devdesc {int /*<<< orphan*/  d_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  OF_close (int /*<<< orphan*/ ) ; 
 struct ofw_devdesc* kdp ; 

__attribute__((used)) static int
ofwd_close(struct open_file *f)
{
	struct ofw_devdesc *dev = f->f_devdata;

	if (dev == kdp) {
#if !defined(__powerpc__)
		OF_close(dev->d_handle);
#endif
		kdp = NULL;
	}
	return (0);
}