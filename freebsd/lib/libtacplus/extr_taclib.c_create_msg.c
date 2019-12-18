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
struct tac_msg {int type; scalar_t__ flags; int /*<<< orphan*/  version; } ;
struct tac_handle {int /*<<< orphan*/ * avs; int /*<<< orphan*/  user_msg; int /*<<< orphan*/  data; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  port; int /*<<< orphan*/  user; struct tac_msg request; scalar_t__ last_seq_no; } ;

/* Variables and functions */
 int MAXAVPAIRS ; 
 int /*<<< orphan*/  free_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  protocol_version (int,int,int) ; 

__attribute__((used)) static void
create_msg(struct tac_handle *h, int msg_type, int var, int type)
{
	struct tac_msg *msg;
	int i;

	h->last_seq_no = 0;

	msg = &h->request;
	msg->type = msg_type;
	msg->version = protocol_version(msg_type, var, type);
	msg->flags = 0; /* encrypted packet body */

	free_str(&h->user);
	free_str(&h->port);
	free_str(&h->rem_addr);
	free_str(&h->data);
	free_str(&h->user_msg);

	for (i=0; i<MAXAVPAIRS; i++)
		free_str(&(h->avs[i]));
}