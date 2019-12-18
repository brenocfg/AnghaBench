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
struct sshkey {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ KEY_RSA ; 
 int /*<<< orphan*/  SSH_AGENT_RSA_SHA2_256 ; 
 int /*<<< orphan*/  SSH_AGENT_RSA_SHA2_512 ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static u_int
agent_encode_alg(const struct sshkey *key, const char *alg)
{
	if (alg != NULL && key->type == KEY_RSA) {
		if (strcmp(alg, "rsa-sha2-256") == 0)
			return SSH_AGENT_RSA_SHA2_256;
		else if (strcmp(alg, "rsa-sha2-512") == 0)
			return SSH_AGENT_RSA_SHA2_512;
	}
	return 0;
}