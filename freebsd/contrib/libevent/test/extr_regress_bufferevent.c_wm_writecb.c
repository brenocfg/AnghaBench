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
struct bufferevent {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  evbuffer_drain (int /*<<< orphan*/ ,int) ; 
 int evbuffer_get_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_ok ; 

__attribute__((used)) static void
wm_writecb(struct bufferevent *bev, void *arg)
{
	assert(evbuffer_get_length(bev->output) <= 100);
	if (evbuffer_get_length(bev->output) == 0) {
		evbuffer_drain(bev->output, evbuffer_get_length(bev->output));
		test_ok++;
	}
}