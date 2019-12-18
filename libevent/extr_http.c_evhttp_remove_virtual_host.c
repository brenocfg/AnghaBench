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
struct evhttp {int /*<<< orphan*/ * vhost_pattern; int /*<<< orphan*/  virtualhosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct evhttp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  next_vhost ; 

int
evhttp_remove_virtual_host(struct evhttp* http, struct evhttp* vhost)
{
	if (vhost->vhost_pattern == NULL)
		return (-1);

	TAILQ_REMOVE(&http->virtualhosts, vhost, next_vhost);

	mm_free(vhost->vhost_pattern);
	vhost->vhost_pattern = NULL;

	return (0);
}