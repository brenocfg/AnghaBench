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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {scalar_t__ ifmb_word; int /*<<< orphan*/  ifmb_baudrate; } ;

/* Variables and functions */
 scalar_t__ IFM_TYPE_MATCH (int,scalar_t__) ; 
 TYPE_1__* ifmedia_baudrate_descriptions ; 

uint64_t
ifmedia_baudrate(int mword)
{
	int i;

	for (i = 0; ifmedia_baudrate_descriptions[i].ifmb_word != 0; i++) {
		if (IFM_TYPE_MATCH(mword, ifmedia_baudrate_descriptions[i].ifmb_word))
			return (ifmedia_baudrate_descriptions[i].ifmb_baudrate);
	}

	/* Not known. */
	return (0);
}