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
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  bufferevent_disable (struct bufferevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  got_readcb ; 

__attribute__((used)) static void
async_readcb(struct bufferevent *bev, void *arg)
{
	/* Disabling read should cause the loop to quit */
	bufferevent_disable(bev, EV_READ);
	got_readcb++;
}