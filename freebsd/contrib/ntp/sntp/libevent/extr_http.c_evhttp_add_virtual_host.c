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
struct evhttp {int /*<<< orphan*/  virtualhosts; int /*<<< orphan*/ * vhost_pattern; int /*<<< orphan*/  sockets; } ;

/* Variables and functions */
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct evhttp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mm_strdup (char const*) ; 
 int /*<<< orphan*/  next_vhost ; 

int
evhttp_add_virtual_host(struct evhttp* http, const char *pattern,
    struct evhttp* vhost)
{
	/* a vhost can only be a vhost once and should not have bound sockets */
	if (vhost->vhost_pattern != NULL ||
	    TAILQ_FIRST(&vhost->sockets) != NULL)
		return (-1);

	vhost->vhost_pattern = mm_strdup(pattern);
	if (vhost->vhost_pattern == NULL)
		return (-1);

	TAILQ_INSERT_TAIL(&http->virtualhosts, vhost, next_vhost);

	return (0);
}