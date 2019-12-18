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
typedef  scalar_t__ uint64_t ;
struct pt_time_cal {int dummy; } ;
struct pt_time {int dummy; } ;
struct TYPE_2__ {scalar_t__ begin; } ;
struct pt_query_decoder {TYPE_1__ config; scalar_t__ pos; struct pt_time_cal tcal; struct pt_time time; } ;

/* Variables and functions */
 int pt_qry_event_ovf_disabled (struct pt_query_decoder*) ; 
 int pte_internal ; 

__attribute__((used)) static int skd010_recover_disabled(struct pt_query_decoder *decoder,
				   const struct pt_time_cal *tcal,
				   const struct pt_time *time, uint64_t offset)
{
	if (!decoder || !tcal || !time)
		return -pte_internal;

	decoder->time = *time;
	decoder->tcal = *tcal;

	/* We continue decoding at the given offset. */
	decoder->pos = decoder->config.begin + offset;

	return pt_qry_event_ovf_disabled(decoder);
}