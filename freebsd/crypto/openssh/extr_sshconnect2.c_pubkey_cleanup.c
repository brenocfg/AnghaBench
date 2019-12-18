#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int agent_fd; int /*<<< orphan*/  keys; } ;
struct TYPE_7__ {struct TYPE_7__* filename; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Identity ;
typedef  TYPE_2__ Authctxt ;

/* Variables and functions */
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ssh_close_authentication_socket (int) ; 
 int /*<<< orphan*/  sshkey_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pubkey_cleanup(Authctxt *authctxt)
{
	Identity *id;

	if (authctxt->agent_fd != -1)
		ssh_close_authentication_socket(authctxt->agent_fd);
	for (id = TAILQ_FIRST(&authctxt->keys); id;
	    id = TAILQ_FIRST(&authctxt->keys)) {
		TAILQ_REMOVE(&authctxt->keys, id, next);
		sshkey_free(id->key);
		free(id->filename);
		free(id);
	}
}