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
struct TYPE_2__ {size_t pos_in_chain; scalar_t__ chain; } ;
struct evbuffer_ptr {size_t pos; TYPE_1__ internal_; } ;
struct evbuffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVBUFFER_PTR_SET ; 
 int evbuffer_ptr_set (struct evbuffer*,struct evbuffer_ptr*,size_t const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
evbuffer_ptr_subtract(struct evbuffer *buf, struct evbuffer_ptr *pos,
    size_t howfar)
{
	if (pos->pos < 0)
		return -1;
	if (howfar > (size_t)pos->pos)
		return -1;
	if (pos->internal_.chain && howfar <= pos->internal_.pos_in_chain) {
		pos->internal_.pos_in_chain -= howfar;
		pos->pos -= howfar;
		return 0;
	} else {
		const size_t newpos = pos->pos - howfar;
		/* Here's the inefficient part: it walks over the
		 * chains until we hit newpos. */
		return evbuffer_ptr_set(buf, pos, newpos, EVBUFFER_PTR_SET);
	}
}