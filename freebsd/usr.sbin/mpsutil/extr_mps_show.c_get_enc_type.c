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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static char *
get_enc_type(uint32_t flags, int *issep)
{
	char *type;

	*issep = 0;
	switch (flags & 0xf) {
	case 0x01:
		type = "Direct Attached SES-2";
		*issep = 1;
		break;
	case 0x02:
		type = "Direct Attached SGPIO";
		break;
	case 0x03:
		type = "Expander SGPIO";
		break;
	case 0x04:
		type = "External SES-2";
		*issep = 1;
		break;
	case 0x05:
		type = "Direct Attached GPIO";
		break;
	case 0x0:
	default:
		return ("Unknown");
	}

	return (type);
}