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
struct openbsd_driver_data {int /*<<< orphan*/  sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct openbsd_driver_data*) ; 

__attribute__((used)) static void
wpa_driver_openbsd_deinit(void *priv)
{
	struct openbsd_driver_data *drv = priv;

	close(drv->sock);
	os_free(drv);
}