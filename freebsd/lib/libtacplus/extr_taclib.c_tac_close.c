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
struct tac_handle {int fd; int num_servers; int /*<<< orphan*/ * avs; int /*<<< orphan*/  user_msg; int /*<<< orphan*/  data; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  port; int /*<<< orphan*/  user; TYPE_1__* servers; } ;
struct TYPE_2__ {struct tac_handle* secret; } ;

/* Variables and functions */
 int MAXAVPAIRS ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (struct tac_handle*) ; 
 int /*<<< orphan*/  free_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tac_handle*,int /*<<< orphan*/ ,int) ; 
 int strlen (struct tac_handle*) ; 

void
tac_close(struct tac_handle *h)
{
	int i, srv;

	if (h->fd != -1)
		close(h->fd);
	for (srv = 0;  srv < h->num_servers;  srv++) {
		memset(h->servers[srv].secret, 0,
		    strlen(h->servers[srv].secret));
		free(h->servers[srv].secret);
	}
	free_str(&h->user);
	free_str(&h->port);
	free_str(&h->rem_addr);
	free_str(&h->data);
	free_str(&h->user_msg);
	for (i=0; i<MAXAVPAIRS; i++)
		free_str(&(h->avs[i]));

	/* Clear everything else before freeing memory */
	memset(h, 0, sizeof(struct tac_handle));
	free(h);
}