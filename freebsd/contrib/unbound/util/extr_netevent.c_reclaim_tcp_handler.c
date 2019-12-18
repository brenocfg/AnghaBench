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
struct comm_point {scalar_t__ type; TYPE_1__* tcp_parent; struct comm_point* tcp_free; int /*<<< orphan*/ * ssl; } ;
struct TYPE_2__ {struct comm_point* tcp_free; int /*<<< orphan*/  cur_tcp_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_shutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comm_point_close (struct comm_point*) ; 
 int /*<<< orphan*/  comm_point_start_listening (TYPE_1__*,int,int) ; 
 scalar_t__ comm_tcp ; 
 int /*<<< orphan*/  log_assert (int) ; 

__attribute__((used)) static void
reclaim_tcp_handler(struct comm_point* c)
{
	log_assert(c->type == comm_tcp);
	if(c->ssl) {
#ifdef HAVE_SSL
		SSL_shutdown(c->ssl);
		SSL_free(c->ssl);
		c->ssl = NULL;
#endif
	}
	comm_point_close(c);
	if(c->tcp_parent) {
		c->tcp_parent->cur_tcp_count--;
		c->tcp_free = c->tcp_parent->tcp_free;
		c->tcp_parent->tcp_free = c;
		if(!c->tcp_free) {
			/* re-enable listening on accept socket */
			comm_point_start_listening(c->tcp_parent, -1, -1);
		}
	}
}