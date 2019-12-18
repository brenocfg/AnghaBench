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
struct nbd_sock {int fallback_index; scalar_t__ dead; } ;
struct nbd_device {int /*<<< orphan*/  disk; struct nbd_config* config; } ;
struct nbd_config {int num_connections; struct nbd_sock** socks; int /*<<< orphan*/  runtime_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NBD_RT_DISCONNECTED ; 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  disk_to_dev (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int find_fallback(struct nbd_device *nbd, int index)
{
	struct nbd_config *config = nbd->config;
	int new_index = -1;
	struct nbd_sock *nsock = config->socks[index];
	int fallback = nsock->fallback_index;

	if (test_bit(NBD_RT_DISCONNECTED, &config->runtime_flags))
		return new_index;

	if (config->num_connections <= 1) {
		dev_err_ratelimited(disk_to_dev(nbd->disk),
				    "Attempted send on invalid socket\n");
		return new_index;
	}

	if (fallback >= 0 && fallback < config->num_connections &&
	    !config->socks[fallback]->dead)
		return fallback;

	if (nsock->fallback_index < 0 ||
	    nsock->fallback_index >= config->num_connections ||
	    config->socks[nsock->fallback_index]->dead) {
		int i;
		for (i = 0; i < config->num_connections; i++) {
			if (i == index)
				continue;
			if (!config->socks[i]->dead) {
				new_index = i;
				break;
			}
		}
		nsock->fallback_index = new_index;
		if (new_index < 0) {
			dev_err_ratelimited(disk_to_dev(nbd->disk),
					    "Dead connection, failed to find a fallback\n");
			return new_index;
		}
	}
	new_index = nsock->fallback_index;
	return new_index;
}