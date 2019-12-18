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
struct uio {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_console (struct uio*) ; 
 int ttydev_write (struct cdev*,struct uio*,int) ; 

__attribute__((used)) static int
ttyconsdev_write(struct cdev *dev, struct uio *uio, int ioflag)
{

	log_console(uio);

	return (ttydev_write(dev, uio, ioflag));
}