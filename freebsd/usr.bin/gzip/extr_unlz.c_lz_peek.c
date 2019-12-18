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
struct lz_decoder {unsigned int pos; size_t dict_size; int /*<<< orphan*/ * obuf; scalar_t__ wrapped; } ;
typedef  size_t off_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t
lz_peek(const struct lz_decoder *lz, unsigned ahead)
{
	off_t diff = lz->pos - ahead - 1;

	if (diff >= 0)
		return lz->obuf[diff];

	if (lz->wrapped)
		return lz->obuf[lz->dict_size + diff];

	return 0;
}