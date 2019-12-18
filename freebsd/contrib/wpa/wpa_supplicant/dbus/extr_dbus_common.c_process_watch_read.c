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

/* Variables and functions */
 int /*<<< orphan*/  EVENT_TYPE_READ ; 
 int /*<<< orphan*/  process_watch (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_watch_read(int sock, void *eloop_ctx, void *sock_ctx)
{
	process_watch(eloop_ctx, sock_ctx, EVENT_TYPE_READ);
}