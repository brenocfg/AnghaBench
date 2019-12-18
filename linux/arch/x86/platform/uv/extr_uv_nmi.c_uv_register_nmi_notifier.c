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

/* Variables and functions */
 int /*<<< orphan*/  NMI_LOCAL ; 
 int /*<<< orphan*/  NMI_UNKNOWN ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ register_nmi_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uv_handle_nmi ; 
 int /*<<< orphan*/  uv_handle_nmi_ping ; 

__attribute__((used)) static void uv_register_nmi_notifier(void)
{
	if (register_nmi_handler(NMI_UNKNOWN, uv_handle_nmi, 0, "uv"))
		pr_warn("UV: NMI handler failed to register\n");

	if (register_nmi_handler(NMI_LOCAL, uv_handle_nmi_ping, 0, "uvping"))
		pr_warn("UV: PING NMI handler failed to register\n");
}