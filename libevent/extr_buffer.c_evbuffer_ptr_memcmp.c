#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t pos_in_chain; struct evbuffer_chain* chain; } ;
struct evbuffer_ptr {scalar_t__ pos; TYPE_1__ internal_; } ;
struct evbuffer_chain {size_t off; struct evbuffer_chain* next; scalar_t__ misalign; scalar_t__ buffer; } ;
struct evbuffer {scalar_t__ total_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EVBUFFER_LOCKED (struct evbuffer const*) ; 
 size_t EV_SIZE_MAX ; 
 int memcmp (scalar_t__,char const*,size_t) ; 

__attribute__((used)) static int
evbuffer_ptr_memcmp(const struct evbuffer *buf, const struct evbuffer_ptr *pos,
    const char *mem, size_t len)
{
	struct evbuffer_chain *chain;
	size_t position;
	int r;

	ASSERT_EVBUFFER_LOCKED(buf);

	if (pos->pos < 0 ||
	    EV_SIZE_MAX - len < (size_t)pos->pos ||
	    pos->pos + len > buf->total_len)
		return -1;

	chain = pos->internal_.chain;
	position = pos->internal_.pos_in_chain;
	while (len && chain) {
		size_t n_comparable;
		if (len + position > chain->off)
			n_comparable = chain->off - position;
		else
			n_comparable = len;
		r = memcmp(chain->buffer + chain->misalign + position, mem,
		    n_comparable);
		if (r)
			return r;
		mem += n_comparable;
		len -= n_comparable;
		position = 0;
		chain = chain->next;
	}

	return 0;
}