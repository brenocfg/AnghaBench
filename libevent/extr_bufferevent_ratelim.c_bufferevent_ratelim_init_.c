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
struct TYPE_2__ {int /*<<< orphan*/  input; } ;
struct bufferevent_private {int /*<<< orphan*/  max_single_read; TYPE_1__ bev; int /*<<< orphan*/  max_single_write; int /*<<< orphan*/ * rate_limiting; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SINGLE_READ_DEFAULT ; 
 int /*<<< orphan*/  MAX_SINGLE_WRITE_DEFAULT ; 
 scalar_t__ evbuffer_set_max_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bufferevent_ratelim_init_(struct bufferevent_private *bev)
{
	bev->rate_limiting = NULL;
	bev->max_single_read = MAX_SINGLE_READ_DEFAULT;
	bev->max_single_write = MAX_SINGLE_WRITE_DEFAULT;

	if (evbuffer_set_max_read(bev->bev.input, bev->max_single_read))
		return -1;

	return 0;
}