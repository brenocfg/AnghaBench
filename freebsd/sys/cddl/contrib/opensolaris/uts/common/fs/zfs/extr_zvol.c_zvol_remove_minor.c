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
typedef  int /*<<< orphan*/  zvol_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 
 int /*<<< orphan*/ * zvol_minor_lookup (char const*) ; 
 int zvol_remove_zv (int /*<<< orphan*/ *) ; 

int
zvol_remove_minor(const char *name)
{
	zvol_state_t *zv;
	int rc;

	mutex_enter(&zfsdev_state_lock);
	if ((zv = zvol_minor_lookup(name)) == NULL) {
		mutex_exit(&zfsdev_state_lock);
		return (SET_ERROR(ENXIO));
	}
	rc = zvol_remove_zv(zv);
	mutex_exit(&zfsdev_state_lock);
	return (rc);
}