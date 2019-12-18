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
struct tnc_if_imv {int /*<<< orphan*/ * path; int /*<<< orphan*/  name; int /*<<< orphan*/ * dlhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  RTLD_LAZY ; 
 int /*<<< orphan*/  dlerror () ; 
 int /*<<< orphan*/ * dlopen (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tncs_imv_initialize (struct tnc_if_imv*) ; 
 scalar_t__ tncs_imv_provide_bind_function (struct tnc_if_imv*) ; 
 scalar_t__ tncs_imv_resolve_funcs (struct tnc_if_imv*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int tncs_load_imv(struct tnc_if_imv *imv)
{
	if (imv->path == NULL) {
		wpa_printf(MSG_DEBUG, "TNC: No IMV configured");
		return -1;
	}

	wpa_printf(MSG_DEBUG, "TNC: Opening IMV: %s (%s)",
		   imv->name, imv->path);
	imv->dlhandle = dlopen(imv->path, RTLD_LAZY);
	if (imv->dlhandle == NULL) {
		wpa_printf(MSG_ERROR, "TNC: Failed to open IMV '%s' (%s): %s",
			   imv->name, imv->path, dlerror());
		return -1;
	}

	if (tncs_imv_resolve_funcs(imv) < 0) {
		wpa_printf(MSG_ERROR, "TNC: Failed to resolve IMV functions");
		return -1;
	}

	if (tncs_imv_initialize(imv) < 0 ||
	    tncs_imv_provide_bind_function(imv) < 0) {
		wpa_printf(MSG_ERROR, "TNC: Failed to initialize IMV");
		return -1;
	}

	return 0;
}