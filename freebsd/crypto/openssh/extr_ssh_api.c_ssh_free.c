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
struct ssh {TYPE_1__* kex; int /*<<< orphan*/  private_keys; int /*<<< orphan*/  key; int /*<<< orphan*/  public_keys; } ;
struct key_entry {TYPE_1__* kex; int /*<<< orphan*/  private_keys; int /*<<< orphan*/  key; int /*<<< orphan*/  public_keys; } ;
struct TYPE_2__ {scalar_t__ server; } ;

/* Variables and functions */
 struct ssh* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct ssh*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct ssh*) ; 
 int /*<<< orphan*/  kex_free (TYPE_1__*) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  ssh_packet_close (struct ssh*) ; 
 int /*<<< orphan*/  sshkey_free (int /*<<< orphan*/ ) ; 

void
ssh_free(struct ssh *ssh)
{
	struct key_entry *k;

	ssh_packet_close(ssh);
	/*
	 * we've only created the public keys variants in case we
	 * are a acting as a server.
	 */
	while ((k = TAILQ_FIRST(&ssh->public_keys)) != NULL) {
		TAILQ_REMOVE(&ssh->public_keys, k, next);
		if (ssh->kex && ssh->kex->server)
			sshkey_free(k->key);
		free(k);
	}
	while ((k = TAILQ_FIRST(&ssh->private_keys)) != NULL) {
		TAILQ_REMOVE(&ssh->private_keys, k, next);
		free(k);
	}
	if (ssh->kex)
		kex_free(ssh->kex);
	free(ssh);
}