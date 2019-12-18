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
struct sshkey {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fingerprint_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_FP_DEFAULT ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ options ; 
 char* sshkey_fingerprint (struct sshkey const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshkey_type (struct sshkey const*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
format_key(const struct sshkey *key)
{
	char *ret, *fp = sshkey_fingerprint(key,
	    options.fingerprint_hash, SSH_FP_DEFAULT);

	xasprintf(&ret, "%s %s", sshkey_type(key), fp);
	free(fp);
	return ret;
}