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
struct ssh {TYPE_1__* kex; } ;
struct TYPE_2__ {int (* verify_host_key ) (struct sshkey*,struct ssh*) ;} ;

/* Variables and functions */
 int SSH_ERR_INVALID_ARGUMENT ; 

int
ssh_set_verify_host_key_callback(struct ssh *ssh,
    int (*cb)(struct sshkey *, struct ssh *))
{
	if (cb == NULL || ssh->kex == NULL)
		return SSH_ERR_INVALID_ARGUMENT;

	ssh->kex->verify_host_key = cb;

	return 0;
}