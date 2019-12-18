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
struct tnc_if_imv {scalar_t__ dlhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlclose (scalar_t__) ; 
 int /*<<< orphan*/  tncs_free_imv (struct tnc_if_imv*) ; 
 int /*<<< orphan*/  tncs_imv_terminate (struct tnc_if_imv*) ; 

__attribute__((used)) static void tncs_unload_imv(struct tnc_if_imv *imv)
{
	tncs_imv_terminate(imv);

	if (imv->dlhandle)
		dlclose(imv->dlhandle);

	tncs_free_imv(imv);
}