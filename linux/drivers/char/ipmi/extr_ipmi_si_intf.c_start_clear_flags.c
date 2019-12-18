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
struct smi_info {int /*<<< orphan*/  si_state; } ;

/* Variables and functions */
 unsigned char IPMI_CLEAR_MSG_FLAGS_CMD ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int /*<<< orphan*/  SI_CLEARING_FLAGS ; 
 unsigned char WDT_PRE_TIMEOUT_INT ; 
 int /*<<< orphan*/  start_new_msg (struct smi_info*,unsigned char*,int) ; 

__attribute__((used)) static void start_clear_flags(struct smi_info *smi_info)
{
	unsigned char msg[3];

	/* Make sure the watchdog pre-timeout flag is not set at startup. */
	msg[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg[1] = IPMI_CLEAR_MSG_FLAGS_CMD;
	msg[2] = WDT_PRE_TIMEOUT_INT;

	start_new_msg(smi_info, msg, 3);
	smi_info->si_state = SI_CLEARING_FLAGS;
}