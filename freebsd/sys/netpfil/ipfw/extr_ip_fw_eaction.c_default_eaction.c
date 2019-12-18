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
struct ip_fw_chain {int dummy; } ;
struct ip_fw_args {int dummy; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int IP_FW_DENY ; 

__attribute__((used)) static int
default_eaction(struct ip_fw_chain *ch, struct ip_fw_args *args,
    ipfw_insn *cmd, int *done)
{

	*done = 1; /* terminate the search */
	return (IP_FW_DENY);
}