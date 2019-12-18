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
struct write_state {scalar_t__ niovecs; int /*<<< orphan*/  iovecs; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ writev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
write_state_flush (struct write_state *w)
{
    if (w->niovecs) {
	if (writev (w->fd, w->iovecs, w->niovecs) < 0)
	    err (1, "writev");
	w->niovecs = 0;
    }
}