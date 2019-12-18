#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  read_suspended; } ;
struct bufferevent_pair {TYPE_1__ bev; } ;
struct TYPE_4__ {int enabled; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int EV_READ ; 
 int EV_WRITE ; 
 TYPE_2__* downcast (struct bufferevent_pair*) ; 
 scalar_t__ evbuffer_get_length (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
be_pair_wants_to_talk(struct bufferevent_pair *src,
    struct bufferevent_pair *dst)
{
	return (downcast(src)->enabled & EV_WRITE) &&
	    (downcast(dst)->enabled & EV_READ) &&
	    !dst->bev.read_suspended &&
	    evbuffer_get_length(downcast(src)->output);
}