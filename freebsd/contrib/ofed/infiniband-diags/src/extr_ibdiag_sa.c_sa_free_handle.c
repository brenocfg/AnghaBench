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
struct sa_handle {int /*<<< orphan*/  fd; int /*<<< orphan*/  agent; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sa_handle*) ; 
 int /*<<< orphan*/  umad_close_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umad_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sa_free_handle(struct sa_handle * h)
{
	umad_unregister(h->fd, h->agent);
	umad_close_port(h->fd);
	free(h);
}