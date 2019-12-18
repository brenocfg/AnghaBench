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
struct bufferevent_pair {scalar_t__ partner; } ;
struct bufferevent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bufferevent_decref_and_unlock_ (struct bufferevent*) ; 
 struct bufferevent* downcast (scalar_t__) ; 
 struct bufferevent_pair* upcast (struct bufferevent*) ; 

__attribute__((used)) static inline void
decref_and_unlock(struct bufferevent *b)
{
	struct bufferevent_pair *bevp = upcast(b);
	if (bevp->partner)
		bufferevent_decref_and_unlock_(downcast(bevp->partner));
	bufferevent_decref_and_unlock_(b);
}