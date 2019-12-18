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
struct TYPE_2__ {size_t high; } ;
struct bufferevent {int /*<<< orphan*/  input; int /*<<< orphan*/  output; TYPE_1__ wm_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEV_DEL_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_READ_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  BEV_RESET_GENERIC_WRITE_TIMEOUT (struct bufferevent*) ; 
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  EV_WRITE ; 
 int /*<<< orphan*/  bufferevent_trigger_nolock_ (struct bufferevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_add_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_freeze (int /*<<< orphan*/ ,int) ; 
 size_t evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evbuffer_remove_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  evbuffer_unfreeze (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
be_pair_transfer(struct bufferevent *src, struct bufferevent *dst,
    int ignore_wm)
{
	size_t dst_size;
	size_t n;

	evbuffer_unfreeze(src->output, 1);
	evbuffer_unfreeze(dst->input, 0);

	if (dst->wm_read.high) {
		dst_size = evbuffer_get_length(dst->input);
		if (dst_size < dst->wm_read.high) {
			n = dst->wm_read.high - dst_size;
			evbuffer_remove_buffer(src->output, dst->input, n);
		} else {
			if (!ignore_wm)
				goto done;
			n = evbuffer_get_length(src->output);
			evbuffer_add_buffer(dst->input, src->output);
		}
	} else {
		n = evbuffer_get_length(src->output);
		evbuffer_add_buffer(dst->input, src->output);
	}

	if (n) {
		BEV_RESET_GENERIC_READ_TIMEOUT(dst);

		if (evbuffer_get_length(dst->output))
			BEV_RESET_GENERIC_WRITE_TIMEOUT(dst);
		else
			BEV_DEL_GENERIC_WRITE_TIMEOUT(dst);
	}

	bufferevent_trigger_nolock_(dst, EV_READ, 0);
	bufferevent_trigger_nolock_(src, EV_WRITE, 0);
done:
	evbuffer_freeze(src->output, 1);
	evbuffer_freeze(dst->input, 0);
}