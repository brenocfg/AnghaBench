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
typedef  int uint32_t ;
struct dictionary {int pos; scalar_t__ full; int* buf; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t dict_get(const struct dictionary *dict, uint32_t dist)
{
	size_t offset = dict->pos - dist - 1;

	if (dist >= dict->pos)
		offset += dict->end;

	return dict->full > 0 ? dict->buf[offset] : 0;
}