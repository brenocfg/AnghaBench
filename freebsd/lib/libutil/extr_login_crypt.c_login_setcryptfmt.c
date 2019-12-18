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
typedef  int /*<<< orphan*/  login_cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  crypt_set_format (char const*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 char* login_getcapstr (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

const char *
login_setcryptfmt(login_cap_t *lc, const char *def, const char *error) {
	const char *cipher;

	cipher = login_getcapstr(lc, "passwd_format", def, NULL);
	if (getenv("CRYPT_DEBUG") != NULL)
		fprintf(stderr, "login_setcryptfmt: "
		    "passwd_format = %s\n", cipher);
	if (cipher == NULL)
		return (error);
	if (!crypt_set_format(cipher))
		return (error);
	return (cipher);
}