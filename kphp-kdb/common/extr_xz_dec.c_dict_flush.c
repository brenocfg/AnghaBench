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
typedef  size_t uint32_t ;
struct xz_buf {scalar_t__ out_pos; scalar_t__ out; } ;
struct dictionary {size_t pos; size_t start; scalar_t__ end; size_t buf; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 scalar_t__ DEC_IS_MULTI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,size_t,size_t) ; 

__attribute__((used)) static uint32_t dict_flush(struct dictionary *dict, struct xz_buf *b)
{
	size_t copy_size = dict->pos - dict->start;

	if (DEC_IS_MULTI(dict->mode)) {
		if (dict->pos == dict->end)
			dict->pos = 0;

		memcpy(b->out + b->out_pos, dict->buf + dict->start,
				copy_size);
	}

	dict->start = dict->pos;
	b->out_pos += copy_size;
	return copy_size;
}