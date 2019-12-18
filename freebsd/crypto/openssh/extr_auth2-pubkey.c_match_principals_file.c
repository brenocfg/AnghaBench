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
struct sshkey_cert {int dummy; } ;
struct sshauthopt {int dummy; } ;
struct ssh {int dummy; } ;
struct passwd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  strict_modes; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/ * auth_openprincipals (char*,struct passwd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 TYPE_1__ options ; 
 int process_principals (struct ssh*,int /*<<< orphan*/ *,char*,struct sshkey_cert*,struct sshauthopt**) ; 
 int /*<<< orphan*/  restore_uid () ; 
 int /*<<< orphan*/  temporarily_use_uid (struct passwd*) ; 

__attribute__((used)) static int
match_principals_file(struct ssh *ssh, struct passwd *pw, char *file,
    struct sshkey_cert *cert, struct sshauthopt **authoptsp)
{
	FILE *f;
	int success;

	if (authoptsp != NULL)
		*authoptsp = NULL;

	temporarily_use_uid(pw);
	debug("trying authorized principals file %s", file);
	if ((f = auth_openprincipals(file, pw, options.strict_modes)) == NULL) {
		restore_uid();
		return 0;
	}
	success = process_principals(ssh, f, file, cert, authoptsp);
	fclose(f);
	restore_uid();
	return success;
}