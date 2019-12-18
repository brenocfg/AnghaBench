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
typedef  int /*<<< orphan*/  mbedtls_pk_context ;

/* Variables and functions */
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  gen_key (int /*<<< orphan*/ *,unsigned int,int,int) ; 
 int /*<<< orphan*/  mbedtls_pk_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  write_key (int /*<<< orphan*/ *,char*,int) ; 

int rsakey(char **arg)
{
	mbedtls_pk_context key;
	unsigned int ksize = 512;
	int exp = 65537;
	char *path = NULL;
	bool pem = true;

	while (*arg && **arg == '-') {
		if (!strcmp(*arg, "-out") && arg[1]) {
			path = arg[1];
			arg++;
		} else if (!strcmp(*arg, "-3")) {
			exp = 3;
		} else if (!strcmp(*arg, "-der")) {
			pem = false;
		}
		arg++;
	}

	if (*arg)
		ksize = (unsigned int)atoi(*arg);

	gen_key(&key, ksize, exp, pem);
	write_key(&key, path, pem);

	mbedtls_pk_free(&key);

	return 0;
}