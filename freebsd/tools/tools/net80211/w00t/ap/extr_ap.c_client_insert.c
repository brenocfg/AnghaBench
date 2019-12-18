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
 int /*<<< orphan*/  mac2str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

void client_insert(struct params *p, struct client *c)
{
#if 1
	do {
		char mac[6*3];
		
		mac2str(mac, c->mac);
		printf("Adding client %s\n", mac);
	} while(0);
#endif

	c->next = p->clients;
	p->clients = c;
}