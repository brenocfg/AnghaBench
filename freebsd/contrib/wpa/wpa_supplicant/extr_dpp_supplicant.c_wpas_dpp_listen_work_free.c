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
struct wpas_dpp_listen_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  os_free (struct wpas_dpp_listen_work*) ; 

__attribute__((used)) static void wpas_dpp_listen_work_free(struct wpas_dpp_listen_work *lwork)
{
	if (!lwork)
		return;
	os_free(lwork);
}