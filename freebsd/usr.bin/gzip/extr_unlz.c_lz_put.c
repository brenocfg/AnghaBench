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
struct lz_decoder {scalar_t__ pos; scalar_t__ dict_size; int /*<<< orphan*/ * obuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  lz_flush (struct lz_decoder*) ; 

__attribute__((used)) static void
lz_put(struct lz_decoder *lz, uint8_t b)
{
	lz->obuf[lz->pos++] = b;
	if (lz->dict_size == lz->pos)
		lz_flush(lz);
}