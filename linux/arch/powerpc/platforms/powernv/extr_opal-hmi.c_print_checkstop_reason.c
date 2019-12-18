#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {int xstop_type; } ;
struct TYPE_4__ {TYPE_1__ xstop_error; } ;
struct OpalHMIEvent {TYPE_2__ u; } ;

/* Variables and functions */
#define  CHECKSTOP_TYPE_CORE 130 
#define  CHECKSTOP_TYPE_NPU 129 
#define  CHECKSTOP_TYPE_NX 128 
 int /*<<< orphan*/  print_core_checkstop_reason (char const*,struct OpalHMIEvent*) ; 
 int /*<<< orphan*/  print_npu_checkstop_reason (char const*,struct OpalHMIEvent*) ; 
 int /*<<< orphan*/  print_nx_checkstop_reason (char const*,struct OpalHMIEvent*) ; 
 int /*<<< orphan*/  printk (char*,char const*,int) ; 

__attribute__((used)) static void print_checkstop_reason(const char *level,
					struct OpalHMIEvent *hmi_evt)
{
	uint8_t type = hmi_evt->u.xstop_error.xstop_type;
	switch (type) {
	case CHECKSTOP_TYPE_CORE:
		print_core_checkstop_reason(level, hmi_evt);
		break;
	case CHECKSTOP_TYPE_NX:
		print_nx_checkstop_reason(level, hmi_evt);
		break;
	case CHECKSTOP_TYPE_NPU:
		print_npu_checkstop_reason(level, hmi_evt);
		break;
	default:
		printk("%s	Unknown Malfunction Alert of type %d\n",
		       level, type);
		break;
	}
}