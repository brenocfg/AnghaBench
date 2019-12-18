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
struct rc_state {int /*<<< orphan*/  c; scalar_t__ ssl; } ;
struct daemon_remote {int /*<<< orphan*/  active; int /*<<< orphan*/  busy_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_free (scalar_t__) ; 
 int /*<<< orphan*/  SSL_shutdown (scalar_t__) ; 
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct rc_state*) ; 
 int /*<<< orphan*/  state_list_remove_elem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clean_point(struct daemon_remote* rc, struct rc_state* s)
{
	state_list_remove_elem(&rc->busy_list, s->c);
	rc->active --;
	if(s->ssl) {
		SSL_shutdown(s->ssl);
		SSL_free(s->ssl);
	}
	comm_point_delete(s->c);
	free(s);
}