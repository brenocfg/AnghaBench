#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  want_reload; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 TYPE_1__ isc_g_appctx ; 

__attribute__((used)) static void
reload_action(int arg) {
	UNUSED(arg);
	isc_g_appctx.want_reload = ISC_TRUE;
}