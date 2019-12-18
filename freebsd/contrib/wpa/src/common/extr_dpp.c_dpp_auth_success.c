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
struct dpp_authentication {int auth_success; int /*<<< orphan*/  k2; int /*<<< orphan*/  k1; scalar_t__ Lx_len; int /*<<< orphan*/  Lx; scalar_t__ Nx_len; int /*<<< orphan*/  Nx; scalar_t__ Mx_len; int /*<<< orphan*/  Mx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void dpp_auth_success(struct dpp_authentication *auth)
{
	wpa_printf(MSG_DEBUG,
		   "DPP: Authentication success - clear temporary keys");
	os_memset(auth->Mx, 0, sizeof(auth->Mx));
	auth->Mx_len = 0;
	os_memset(auth->Nx, 0, sizeof(auth->Nx));
	auth->Nx_len = 0;
	os_memset(auth->Lx, 0, sizeof(auth->Lx));
	auth->Lx_len = 0;
	os_memset(auth->k1, 0, sizeof(auth->k1));
	os_memset(auth->k2, 0, sizeof(auth->k2));

	auth->auth_success = 1;
}