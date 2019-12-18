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
typedef  int /*<<< orphan*/  uint8_t ;
struct autr_ta {int pending_count; int /*<<< orphan*/  fetched; } ;

/* Variables and functions */

__attribute__((used)) static void
seen_trustanchor(struct autr_ta* ta, uint8_t seen)
{
	ta->fetched = seen;
	if(ta->pending_count < 250) /* no numerical overflow, please */
		ta->pending_count++;
}