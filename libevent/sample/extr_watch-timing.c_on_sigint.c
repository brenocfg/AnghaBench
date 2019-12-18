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
typedef  int /*<<< orphan*/  evutil_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  base ; 
 int /*<<< orphan*/  event_base_loopbreak (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_sigint(evutil_socket_t sig, short events, void *arg)
{
	event_base_loopbreak(base);
}