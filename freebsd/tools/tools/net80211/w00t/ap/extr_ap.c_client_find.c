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
struct params {struct client* clients; } ;
struct client {struct client* next; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

struct client* client_find(struct params *p, char *mac)
{
	struct client* c = p->clients;

	while (c) {
		if (memcmp(c->mac, mac, 6) == 0)
			return c;

		c = c->next;
	}

	return NULL;
}