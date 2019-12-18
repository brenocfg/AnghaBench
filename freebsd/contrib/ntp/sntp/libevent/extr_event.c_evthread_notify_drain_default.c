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
struct event_base {scalar_t__ is_notify_pending; } ;
typedef  int /*<<< orphan*/  evutil_socket_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EVBASE_ACQUIRE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVBASE_RELEASE_LOCK (struct event_base*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  th_base_lock ; 

__attribute__((used)) static void
evthread_notify_drain_default(evutil_socket_t fd, short what, void *arg)
{
	unsigned char buf[1024];
	struct event_base *base = arg;
#ifdef _WIN32
	while (recv(fd, (char*)buf, sizeof(buf), 0) > 0)
		;
#else
	while (read(fd, (char*)buf, sizeof(buf)) > 0)
		;
#endif

	EVBASE_ACQUIRE_LOCK(base, th_base_lock);
	base->is_notify_pending = 0;
	EVBASE_RELEASE_LOCK(base, th_base_lock);
}