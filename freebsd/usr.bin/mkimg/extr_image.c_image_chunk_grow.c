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
struct chunk {size_t ch_size; } ;

/* Variables and functions */
 void* SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static size_t
image_chunk_grow(struct chunk *ch, size_t sz)
{
	size_t dsz, newsz;

	newsz = ch->ch_size + sz;
	if (newsz > ch->ch_size) {
		ch->ch_size = newsz;
		return (0);
	}
	/* We would overflow -- create new chunk for remainder. */
	dsz = SIZE_MAX - ch->ch_size;
	assert(dsz < sz);
	ch->ch_size = SIZE_MAX;
	return (sz - dsz);
}