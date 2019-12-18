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
struct sshauthopt {int dummy; } ;
struct ssh {int dummy; } ;
struct passwd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  strict_modes; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * auth_openkeyfile (char*,struct passwd*,int /*<<< orphan*/ ) ; 
 int check_authkeys_file (struct ssh*,struct passwd*,int /*<<< orphan*/ *,char*,struct sshkey*,struct sshauthopt**) ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 TYPE_1__ options ; 
 int /*<<< orphan*/  restore_uid () ; 
 int /*<<< orphan*/  temporarily_use_uid (struct passwd*) ; 

__attribute__((used)) static int
user_key_allowed2(struct ssh *ssh, struct passwd *pw, struct sshkey *key,
    char *file, struct sshauthopt **authoptsp)
{
	FILE *f;
	int found_key = 0;

	if (authoptsp != NULL)
		*authoptsp = NULL;

	/* Temporarily use the user's uid. */
	temporarily_use_uid(pw);

	debug("trying public key file %s", file);
	if ((f = auth_openkeyfile(file, pw, options.strict_modes)) != NULL) {
		found_key = check_authkeys_file(ssh, pw, f, file,
		    key, authoptsp);
		fclose(f);
	}

	restore_uid();
	return found_key;
}