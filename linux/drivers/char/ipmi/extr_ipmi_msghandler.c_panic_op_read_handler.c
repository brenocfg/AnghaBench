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
struct kernel_param {int dummy; } ;

/* Variables and functions */
#define  IPMI_SEND_PANIC_EVENT 130 
#define  IPMI_SEND_PANIC_EVENT_NONE 129 
#define  IPMI_SEND_PANIC_EVENT_STRING 128 
 int ipmi_send_panic_event ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int panic_op_read_handler(char *buffer, const struct kernel_param *kp)
{
	switch (ipmi_send_panic_event) {
	case IPMI_SEND_PANIC_EVENT_NONE:
		strcpy(buffer, "none");
		break;

	case IPMI_SEND_PANIC_EVENT:
		strcpy(buffer, "event");
		break;

	case IPMI_SEND_PANIC_EVENT_STRING:
		strcpy(buffer, "string");
		break;

	default:
		strcpy(buffer, "???");
		break;
	}

	return strlen(buffer);
}