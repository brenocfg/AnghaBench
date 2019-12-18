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
struct TYPE_2__ {int /*<<< orphan*/ * bitmap; int /*<<< orphan*/  fd; int /*<<< orphan*/ * file; } ;
struct ubd {TYPE_1__ cow; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_close_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ubd_close_dev(struct ubd *ubd_dev)
{
	os_close_file(ubd_dev->fd);
	if(ubd_dev->cow.file == NULL)
		return;

	os_close_file(ubd_dev->cow.fd);
	vfree(ubd_dev->cow.bitmap);
	ubd_dev->cow.bitmap = NULL;
}