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
struct dictionary {scalar_t__ pos; scalar_t__ full; int /*<<< orphan*/ * buf; } ;

/* Variables and functions */

__attribute__((used)) static inline void dict_put(struct dictionary *dict, uint8_t byte)
{
	dict->buf[dict->pos++] = byte;

	if (dict->full < dict->pos)
		dict->full = dict->pos;
}