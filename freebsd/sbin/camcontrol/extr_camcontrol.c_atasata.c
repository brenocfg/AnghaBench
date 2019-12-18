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
struct ata_params {int satacapabilities; } ;

/* Variables and functions */

__attribute__((used)) static int
atasata(struct ata_params *parm)
{


	if (parm->satacapabilities != 0xffff &&
	    parm->satacapabilities != 0x0000)
		return 1;

	return 0;
}