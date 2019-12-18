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
 int evbuffer_add (int /*<<< orphan*/ ,void const*,size_t) ; 

int
bufferevent_write(struct bufferevent *bufev, const void *data, size_t size)
{
	if (evbuffer_add(bufev->output, data, size) == -1)
		return (-1);

	return 0;
}