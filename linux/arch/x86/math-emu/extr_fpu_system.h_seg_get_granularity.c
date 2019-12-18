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
struct desc_struct {scalar_t__ g; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long seg_get_granularity(struct desc_struct *d)
{
	return d->g ? 4096 : 1;
}