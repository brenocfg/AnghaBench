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
#define  STA_DEAUTH 132 
#define  STA_DISASSOC 131 
#define  STA_DISASSOC_FROM_CLI 130 
#define  STA_NULLFUNC 129 
#define  STA_REMOVE 128 

__attribute__((used)) static const char * timeout_next_str(int val)
{
	switch (val) {
	case STA_NULLFUNC:
		return "NULLFUNC POLL";
	case STA_DISASSOC:
		return "DISASSOC";
	case STA_DEAUTH:
		return "DEAUTH";
	case STA_REMOVE:
		return "REMOVE";
	case STA_DISASSOC_FROM_CLI:
		return "DISASSOC_FROM_CLI";
	}

	return "?";
}