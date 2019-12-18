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
struct sshkey {int /*<<< orphan*/  type; int /*<<< orphan*/ * cert; } ;

/* Variables and functions */
 int SSH_ERR_KEY_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  cert_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshkey_type_is_cert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_type_plain (int /*<<< orphan*/ ) ; 

int
sshkey_drop_cert(struct sshkey *k)
{
	if (!sshkey_type_is_cert(k->type))
		return SSH_ERR_KEY_TYPE_UNKNOWN;
	cert_free(k->cert);
	k->cert = NULL;
	k->type = sshkey_type_plain(k->type);
	return 0;
}