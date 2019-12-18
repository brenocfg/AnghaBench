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
struct sshkey {TYPE_1__* cert; } ;
struct sshauthopt {int dummy; } ;
struct ssh {int dummy; } ;
struct passwd {int dummy; } ;
struct TYPE_4__ {size_t num_authkeys_files; int /*<<< orphan*/ * authorized_keys_files; } ;
struct TYPE_3__ {struct sshkey* signature_key; } ;

/* Variables and functions */
 scalar_t__ auth_key_is_revoked (struct sshkey*) ; 
 char* expand_authorized_keys (int /*<<< orphan*/ ,struct passwd*) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__ options ; 
 int /*<<< orphan*/  sshauthopt_free (struct sshauthopt*) ; 
 scalar_t__ sshkey_is_cert (struct sshkey*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 size_t user_cert_trusted_ca (struct ssh*,struct passwd*,struct sshkey*,struct sshauthopt**) ; 
 size_t user_key_allowed2 (struct ssh*,struct passwd*,struct sshkey*,char*,struct sshauthopt**) ; 
 size_t user_key_command_allowed2 (struct ssh*,struct passwd*,struct sshkey*,struct sshauthopt**) ; 

int
user_key_allowed(struct ssh *ssh, struct passwd *pw, struct sshkey *key,
    int auth_attempt, struct sshauthopt **authoptsp)
{
	u_int success, i;
	char *file;
	struct sshauthopt *opts = NULL;
	if (authoptsp != NULL)
		*authoptsp = NULL;

	if (auth_key_is_revoked(key))
		return 0;
	if (sshkey_is_cert(key) &&
	    auth_key_is_revoked(key->cert->signature_key))
		return 0;

	if ((success = user_cert_trusted_ca(ssh, pw, key, &opts)) != 0)
		goto out;
	sshauthopt_free(opts);
	opts = NULL;

	if ((success = user_key_command_allowed2(ssh, pw, key, &opts)) != 0)
		goto out;
	sshauthopt_free(opts);
	opts = NULL;

	for (i = 0; !success && i < options.num_authkeys_files; i++) {
		if (strcasecmp(options.authorized_keys_files[i], "none") == 0)
			continue;
		file = expand_authorized_keys(
		    options.authorized_keys_files[i], pw);
		success = user_key_allowed2(ssh, pw, key, file, &opts);
		free(file);
	}

 out:
	if (success && authoptsp != NULL) {
		*authoptsp = opts;
		opts = NULL;
	}
	sshauthopt_free(opts);
	return success;
}