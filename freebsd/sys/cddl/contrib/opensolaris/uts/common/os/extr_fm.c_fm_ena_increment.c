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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int ENA_FMT1_GEN_SHFT ; 
 int ENA_FMT2_GEN_SHFT ; 
 int ENA_FORMAT (int /*<<< orphan*/ ) ; 
#define  FM_ENA_FMT1 129 
#define  FM_ENA_FMT2 128 

uint64_t
fm_ena_increment(uint64_t ena)
{
	uint64_t new_ena;

	switch (ENA_FORMAT(ena)) {
	case FM_ENA_FMT1:
		new_ena = ena + (1 << ENA_FMT1_GEN_SHFT);
		break;
	case FM_ENA_FMT2:
		new_ena = ena + (1 << ENA_FMT2_GEN_SHFT);
		break;
	default:
		new_ena = 0;
	}

	return (new_ena);
}