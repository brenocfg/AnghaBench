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
struct ieee802_1x_cp_sm {int /*<<< orphan*/  connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  SECURE ; 

void ieee802_1x_cp_connect_secure(void *cp_ctx)
{
	struct ieee802_1x_cp_sm *sm = cp_ctx;

	sm->connect = SECURE;
}