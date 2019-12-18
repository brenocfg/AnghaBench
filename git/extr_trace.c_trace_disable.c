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
struct trace_key {int initialized; scalar_t__ need_close; scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (scalar_t__) ; 

void trace_disable(struct trace_key *key)
{
	if (key->need_close)
		close(key->fd);
	key->fd = 0;
	key->initialized = 1;
	key->need_close = 0;
}