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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SYSMOUSE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sysmouse_buffer ; 
 scalar_t__ sysmouse_level ; 
 int /*<<< orphan*/  sysmouse_lock ; 

__attribute__((used)) static int
sysmouse_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{

	mtx_lock(&sysmouse_lock);
	free(sysmouse_buffer, M_SYSMOUSE);
	sysmouse_buffer = NULL;
	sysmouse_level = 0;
	mtx_unlock(&sysmouse_lock);

	return (0);
}