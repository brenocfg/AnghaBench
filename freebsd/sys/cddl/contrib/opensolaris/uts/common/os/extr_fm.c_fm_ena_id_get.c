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
typedef  int uint64_t ;

/* Variables and functions */
 int ENA_FMT1_ID_MASK ; 
 int ENA_FMT1_ID_SHFT ; 
 int ENA_FMT2_ID_MASK ; 
 int ENA_FMT2_ID_SHFT ; 
 int ENA_FORMAT (int) ; 
#define  FM_ENA_FMT1 129 
#define  FM_ENA_FMT2 128 

uint64_t
fm_ena_id_get(uint64_t ena)
{
	uint64_t id;

	switch (ENA_FORMAT(ena)) {
	case FM_ENA_FMT1:
		id = (ena & ENA_FMT1_ID_MASK) >> ENA_FMT1_ID_SHFT;
		break;
	case FM_ENA_FMT2:
		id = (ena & ENA_FMT2_ID_MASK) >> ENA_FMT2_ID_SHFT;
		break;
	default:
		id = 0;
	}

	return (id);
}