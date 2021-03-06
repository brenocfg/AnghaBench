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
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_parse_phandle_with_args (struct device_node*,char*,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scmi_mailbox_check(struct device_node *np, int idx)
{
	return of_parse_phandle_with_args(np, "mboxes", "#mbox-cells",
					  idx, NULL);
}