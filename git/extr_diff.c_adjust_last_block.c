#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct diff_options {scalar_t__ color_moved; TYPE_2__* emitted_symbols; } ;
struct TYPE_4__ {TYPE_1__* buf; } ;
struct TYPE_3__ {char* line; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int COLOR_MOVED_MIN_ALNUM_COUNT ; 
 scalar_t__ COLOR_MOVED_PLAIN ; 
 int /*<<< orphan*/  DIFF_SYMBOL_MOVED_LINE ; 
 int /*<<< orphan*/  isalnum (char const) ; 

__attribute__((used)) static int adjust_last_block(struct diff_options *o, int n, int block_length)
{
	int i, alnum_count = 0;
	if (o->color_moved == COLOR_MOVED_PLAIN)
		return block_length;
	for (i = 1; i < block_length + 1; i++) {
		const char *c = o->emitted_symbols->buf[n - i].line;
		for (; *c; c++) {
			if (!isalnum(*c))
				continue;
			alnum_count++;
			if (alnum_count >= COLOR_MOVED_MIN_ALNUM_COUNT)
				return 1;
		}
	}
	for (i = 1; i < block_length + 1; i++)
		o->emitted_symbols->buf[n - i].flags &= ~DIFF_SYMBOL_MOVED_LINE;
	return 0;
}