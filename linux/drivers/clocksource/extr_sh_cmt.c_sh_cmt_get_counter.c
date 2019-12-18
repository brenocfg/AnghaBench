#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct sh_cmt_channel {TYPE_2__* cmt; } ;
struct TYPE_4__ {TYPE_1__* info; } ;
struct TYPE_3__ {scalar_t__ overflow_bit; } ;

/* Variables and functions */
 scalar_t__ sh_cmt_read_cmcnt (struct sh_cmt_channel*) ; 
 scalar_t__ sh_cmt_read_cmcsr (struct sh_cmt_channel*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u32 sh_cmt_get_counter(struct sh_cmt_channel *ch, u32 *has_wrapped)
{
	u32 v1, v2, v3;
	u32 o1, o2;

	o1 = sh_cmt_read_cmcsr(ch) & ch->cmt->info->overflow_bit;

	/* Make sure the timer value is stable. Stolen from acpi_pm.c */
	do {
		o2 = o1;
		v1 = sh_cmt_read_cmcnt(ch);
		v2 = sh_cmt_read_cmcnt(ch);
		v3 = sh_cmt_read_cmcnt(ch);
		o1 = sh_cmt_read_cmcsr(ch) & ch->cmt->info->overflow_bit;
	} while (unlikely((o1 != o2) || (v1 > v2 && v1 < v3)
			  || (v2 > v3 && v2 < v1) || (v3 > v1 && v3 < v2)));

	*has_wrapped = o1;
	return v2;
}