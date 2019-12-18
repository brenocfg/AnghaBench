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
struct mesh_rsn {scalar_t__ auth; scalar_t__ igtk_len; int /*<<< orphan*/  igtk; scalar_t__ mgtk_len; int /*<<< orphan*/  mgtk; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_deinit (scalar_t__) ; 

__attribute__((used)) static void mesh_rsn_deinit(struct mesh_rsn *rsn)
{
	os_memset(rsn->mgtk, 0, sizeof(rsn->mgtk));
	rsn->mgtk_len = 0;
	os_memset(rsn->igtk, 0, sizeof(rsn->igtk));
	rsn->igtk_len = 0;
	if (rsn->auth)
		wpa_deinit(rsn->auth);
}