#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* phase; void* range; void* freq; } ;
typedef  TYPE_1__ SYNTH ;

/* Variables and functions */
 void* get_lsb_int16 (unsigned char**) ; 

void
get_mbg_synth(
	unsigned char **buffpp,
	SYNTH *synthp
	)
{
  synthp->freq  = get_lsb_int16(buffpp);
  synthp->range = get_lsb_int16(buffpp);
  synthp->phase = get_lsb_int16(buffpp);
}