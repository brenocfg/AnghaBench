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
struct pt_query_decoder {int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int pte_internal ; 
 scalar_t__ ptps_pad ; 

int pt_qry_decode_pad(struct pt_query_decoder *decoder)
{
	if (!decoder)
		return -pte_internal;

	decoder->pos += ptps_pad;

	return 0;
}