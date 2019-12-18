#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ hdr_template_req; } ;
struct TYPE_5__ {TYPE_1__ config; } ;
typedef  TYPE_2__ sli4_t ;

/* Variables and functions */
 int SLI4_FCOE_HDR_TEMPLATE_SIZE ; 
 int SLI_ROUND_PAGE (int) ; 

uint32_t
sli_fc_get_rpi_requirements(sli4_t *sli4, uint32_t n_rpi)
{
	uint32_t	bytes = 0;

	/* Check if header templates needed */
	if (sli4->config.hdr_template_req) {
		/* round up to a page */
		bytes = SLI_ROUND_PAGE(n_rpi * SLI4_FCOE_HDR_TEMPLATE_SIZE);
	}

	return bytes;
}