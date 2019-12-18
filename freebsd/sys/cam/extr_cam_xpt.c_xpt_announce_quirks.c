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
struct cam_periph {char* periph_name; int /*<<< orphan*/  unit_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ,int,char*) ; 

void
xpt_announce_quirks(struct cam_periph *periph, int quirks, char *bit_string)
{
	if (quirks != 0) {
		printf("%s%d: quirks=0x%b\n", periph->periph_name,
		    periph->unit_number, quirks, bit_string);
	}
}