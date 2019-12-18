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
typedef  int /*<<< orphan*/  ecard_t ;

/* Variables and functions */
 unsigned int MAX_ECARDS ; 
 int /*<<< orphan*/ ** slot_to_expcard ; 

__attribute__((used)) static inline ecard_t *slot_to_ecard(unsigned int slot)
{
	return slot < MAX_ECARDS ? slot_to_expcard[slot] : NULL;
}