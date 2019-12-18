#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pdu {TYPE_1__* pdu_bhs; } ;
struct TYPE_2__ {scalar_t__* bhs_data_segment_len; } ;

/* Variables and functions */

__attribute__((used)) static int
pdu_data_segment_length(const struct pdu *pdu)
{
	uint32_t len = 0;

	len += pdu->pdu_bhs->bhs_data_segment_len[0];
	len <<= 8;
	len += pdu->pdu_bhs->bhs_data_segment_len[1];
	len <<= 8;
	len += pdu->pdu_bhs->bhs_data_segment_len[2];

	return (len);
}