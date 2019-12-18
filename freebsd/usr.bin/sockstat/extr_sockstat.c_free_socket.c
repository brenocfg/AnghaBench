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
struct sock {struct sock* next; struct sock* faddr; struct sock* laddr; } ;
struct addr {struct addr* next; struct addr* faddr; struct addr* laddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sock*) ; 

__attribute__((used)) static void
free_socket(struct sock *sock)
{
	struct addr *cur, *next;

	cur = sock->laddr;
	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}
	cur = sock->faddr;
	while (cur != NULL) {
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(sock);
}