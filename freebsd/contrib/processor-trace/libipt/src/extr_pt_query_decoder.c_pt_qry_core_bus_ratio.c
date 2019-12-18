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
typedef  int /*<<< orphan*/  uint32_t ;
struct pt_query_decoder {int /*<<< orphan*/  last_time; } ;

/* Variables and functions */
 int pt_time_query_cbr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_invalid ; 

int pt_qry_core_bus_ratio(struct pt_query_decoder *decoder, uint32_t *cbr)
{
	if (!decoder || !cbr)
		return -pte_invalid;

	return pt_time_query_cbr(cbr, &decoder->last_time);
}