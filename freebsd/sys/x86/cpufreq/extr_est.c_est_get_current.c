#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {scalar_t__ id16; } ;
typedef  TYPE_1__ freq_info ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  est_get_id16 (scalar_t__*) ; 

__attribute__((used)) static freq_info *
est_get_current(freq_info *freq_list, size_t tablen)
{
	freq_info *f;
	int i;
	uint16_t id16;

	/*
	 * Try a few times to get a valid value.  Sometimes, if the CPU
	 * is in the middle of an asynchronous transition (i.e., P4TCC),
	 * we get a temporary invalid result.
	 */
	for (i = 0; i < 5; i++) {
		est_get_id16(&id16);
		for (f = freq_list; f < freq_list + tablen; f++) {
			if (f->id16 == id16)
				return (f);
		}
		DELAY(100);
	}
	return (NULL);
}