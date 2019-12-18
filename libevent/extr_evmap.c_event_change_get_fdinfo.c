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
struct evmap_signal {int dummy; } ;
struct evmap_io {int dummy; } ;
typedef  void event_changelist_fdinfo ;
struct event_change {int read_change; int /*<<< orphan*/  fd; } ;
struct event_base {int /*<<< orphan*/  io; int /*<<< orphan*/  sigmap; } ;

/* Variables and functions */
 int EV_CHANGE_SIGNAL ; 
 int /*<<< orphan*/  GET_IO_SLOT (struct evmap_io*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_SIGNAL_SLOT (struct evmap_signal*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evmap_io ; 
 int /*<<< orphan*/  evmap_signal ; 

__attribute__((used)) static inline struct event_changelist_fdinfo *
event_change_get_fdinfo(struct event_base *base,
    const struct event_change *change)
{
	char *ptr;
	if (change->read_change & EV_CHANGE_SIGNAL) {
		struct evmap_signal *ctx;
		GET_SIGNAL_SLOT(ctx, &base->sigmap, change->fd, evmap_signal);
		ptr = ((char*)ctx) + sizeof(struct evmap_signal);
	} else {
		struct evmap_io *ctx;
		GET_IO_SLOT(ctx, &base->io, change->fd, evmap_io);
		ptr = ((char*)ctx) + sizeof(struct evmap_io);
	}
	return (void*)ptr;
}