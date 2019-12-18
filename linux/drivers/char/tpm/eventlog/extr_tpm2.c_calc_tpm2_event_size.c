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
struct tcg_pcr_event2_head {int dummy; } ;
struct tcg_pcr_event {int dummy; } ;

/* Variables and functions */
 size_t __calc_tpm2_event_size (struct tcg_pcr_event2_head*,struct tcg_pcr_event*,int) ; 

__attribute__((used)) static size_t calc_tpm2_event_size(struct tcg_pcr_event2_head *event,
				   struct tcg_pcr_event *event_header)
{
	return __calc_tpm2_event_size(event, event_header, false);
}