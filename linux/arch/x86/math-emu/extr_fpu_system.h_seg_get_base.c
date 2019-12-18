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
struct desc_struct {unsigned long base0; scalar_t__ base1; scalar_t__ base2; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long seg_get_base(struct desc_struct *d)
{
	unsigned long base = (unsigned long)d->base2 << 24;

	return base | ((unsigned long)d->base1 << 16) | d->base0;
}