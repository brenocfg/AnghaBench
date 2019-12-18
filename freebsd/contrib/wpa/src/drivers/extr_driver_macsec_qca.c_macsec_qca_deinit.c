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
struct macsec_qca_data {int /*<<< orphan*/  common; } ;

/* Variables and functions */
 int /*<<< orphan*/  driver_wired_deinit_common (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct macsec_qca_data*) ; 

__attribute__((used)) static void macsec_qca_deinit(void *priv)
{
	struct macsec_qca_data *drv = priv;

	driver_wired_deinit_common(&drv->common);
	os_free(drv);
}