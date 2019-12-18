#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct sshkey {int dummy; } ;
struct TYPE_4__ {size_t num_host_key_files; } ;
struct TYPE_3__ {struct sshkey** host_keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  fatal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ options ; 
 TYPE_1__ sensitive_data ; 
 int /*<<< orphan*/  ssh_err (int) ; 
 int /*<<< orphan*/  sshkey_free (struct sshkey*) ; 
 int sshkey_from_private (struct sshkey*,struct sshkey**) ; 
 int /*<<< orphan*/  sshkey_type (struct sshkey*) ; 

void
demote_sensitive_data(void)
{
	struct sshkey *tmp;
	u_int i;
	int r;

	for (i = 0; i < options.num_host_key_files; i++) {
		if (sensitive_data.host_keys[i]) {
			if ((r = sshkey_from_private(
			    sensitive_data.host_keys[i], &tmp)) != 0)
				fatal("could not demote host %s key: %s",
				    sshkey_type(sensitive_data.host_keys[i]),
				    ssh_err(r));
			sshkey_free(sensitive_data.host_keys[i]);
			sensitive_data.host_keys[i] = tmp;
		}
		/* Certs do not need demotion */
	}
}