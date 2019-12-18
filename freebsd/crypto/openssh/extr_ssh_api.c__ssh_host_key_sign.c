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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sshkey {int dummy; } ;

/* Variables and functions */
 int sshkey_sign (struct sshkey*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/  const*,size_t,char const*,int /*<<< orphan*/ ) ; 

int
_ssh_host_key_sign(struct sshkey *privkey, struct sshkey *pubkey,
    u_char **signature, size_t *slen, const u_char *data, size_t dlen,
    const char *alg, u_int compat)
{
	return sshkey_sign(privkey, signature, slen, data, dlen, alg, compat);
}