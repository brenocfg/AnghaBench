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
struct event_overlapped {int dummy; } ;
typedef  int /*<<< orphan*/  ev_ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  count_incr () ; 
 int /*<<< orphan*/  evbuffer_commit_read_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbuf ; 
 int /*<<< orphan*/  tt_assert (int) ; 

__attribute__((used)) static void
read_complete(struct event_overlapped *eo, uintptr_t key,
    ev_ssize_t nbytes, int ok)
{
	tt_assert(ok);
	evbuffer_commit_read_(rbuf, nbytes);
	count_incr();
end:
	;
}