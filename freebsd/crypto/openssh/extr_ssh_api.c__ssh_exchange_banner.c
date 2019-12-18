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
struct ssh {struct kex* kex; } ;
struct kex {int /*<<< orphan*/ * client_version_string; int /*<<< orphan*/ * server_version_string; scalar_t__ server; } ;

/* Variables and functions */
 int _ssh_order_hostkeyalgs (struct ssh*) ; 
 int _ssh_read_banner (struct ssh*,int /*<<< orphan*/ **) ; 
 int _ssh_send_banner (struct ssh*,int /*<<< orphan*/ **) ; 
 int kex_send_kexinit (struct ssh*) ; 

int
_ssh_exchange_banner(struct ssh *ssh)
{
	struct kex *kex = ssh->kex;
	int r;

	/*
	 * if _ssh_read_banner() cannot parse a full version string
	 * it will return NULL and we end up calling it again.
	 */

	r = 0;
	if (kex->server) {
		if (kex->server_version_string == NULL)
			r = _ssh_send_banner(ssh, &kex->server_version_string);
		if (r == 0 &&
		    kex->server_version_string != NULL &&
		    kex->client_version_string == NULL)
			r = _ssh_read_banner(ssh, &kex->client_version_string);
	} else {
		if (kex->server_version_string == NULL)
			r = _ssh_read_banner(ssh, &kex->server_version_string);
		if (r == 0 &&
		    kex->server_version_string != NULL &&
		    kex->client_version_string == NULL)
			r = _ssh_send_banner(ssh, &kex->client_version_string);
	}
	if (r != 0)
		return r;
	/* start initial kex as soon as we have exchanged the banners */
	if (kex->server_version_string != NULL &&
	    kex->client_version_string != NULL) {
		if ((r = _ssh_order_hostkeyalgs(ssh)) != 0 ||
		    (r = kex_send_kexinit(ssh)) != 0)
			return r;
	}
	return 0;
}