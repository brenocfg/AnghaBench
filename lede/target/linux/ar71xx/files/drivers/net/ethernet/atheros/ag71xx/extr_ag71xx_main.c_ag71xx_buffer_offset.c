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
struct ag71xx {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  is_ar724x; } ;

/* Variables and functions */
 int NET_IP_ALIGN ; 
 int NET_SKB_PAD ; 
 TYPE_1__* ag71xx_get_pdata (struct ag71xx*) ; 
 scalar_t__ ag71xx_has_ar8216 (struct ag71xx*) ; 

__attribute__((used)) static int ag71xx_buffer_offset(struct ag71xx *ag)
{
	int offset = NET_SKB_PAD;

	/*
	 * On AR71xx/AR91xx packets must be 4-byte aligned.
	 *
	 * When using builtin AR8216 support, hardware adds a 2-byte header,
	 * so we don't need any extra alignment in that case.
	 */
	if (!ag71xx_get_pdata(ag)->is_ar724x || ag71xx_has_ar8216(ag))
		return offset;

	return offset + NET_IP_ALIGN;
}