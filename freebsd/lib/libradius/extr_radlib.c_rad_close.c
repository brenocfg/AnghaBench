#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rad_handle {int fd; int num_servers; TYPE_1__* servers; } ;
struct TYPE_2__ {struct rad_handle* secret; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_password (struct rad_handle*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct rad_handle*) ; 
 int /*<<< orphan*/  memset (struct rad_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (struct rad_handle*) ; 

void
rad_close(struct rad_handle *h)
{
	int srv;

	if (h->fd != -1)
		close(h->fd);
	for (srv = 0;  srv < h->num_servers;  srv++) {
		memset(h->servers[srv].secret, 0,
		    strlen(h->servers[srv].secret));
		free(h->servers[srv].secret);
	}
	clear_password(h);
	free(h);
}