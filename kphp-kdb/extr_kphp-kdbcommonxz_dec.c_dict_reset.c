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
struct xz_buf {scalar_t__ out_pos; scalar_t__ out_size; scalar_t__ out; } ;
struct dictionary {scalar_t__ full; scalar_t__ limit; scalar_t__ pos; scalar_t__ start; scalar_t__ end; scalar_t__ buf; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ DEC_IS_SINGLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dict_reset(struct dictionary *dict, struct xz_buf *b)
{
	if (DEC_IS_SINGLE(dict->mode)) {
		dict->buf = b->out + b->out_pos;
		dict->end = b->out_size - b->out_pos;
	}

	dict->start = 0;
	dict->pos = 0;
	dict->limit = 0;
	dict->full = 0;
}