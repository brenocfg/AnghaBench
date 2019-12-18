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
struct pt_query_decoder {int pos; } ;

/* Variables and functions */
 int pte_internal ; 

__attribute__((used)) static int pt_qry_consume_tip_pge(struct pt_query_decoder *decoder, int size)
{
	if (!decoder)
		return -pte_internal;

	decoder->pos += size;
	return 0;
}