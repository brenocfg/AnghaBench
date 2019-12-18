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
typedef  int uint16_t ;
struct pf_tagset {int mask; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t
tag2hashindex(const struct pf_tagset *ts, uint16_t tag)
{

	return (tag & ts->mask);
}