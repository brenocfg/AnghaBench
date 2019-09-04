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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char const*) ; 
 int /*<<< orphan*/  erase_credential () ; 
 int /*<<< orphan*/  get_credential () ; 
 char* host ; 
 int /*<<< orphan*/  load_cred_funcs () ; 
 char* path ; 
 char* protocol ; 
 int /*<<< orphan*/  read_credential () ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  store_credential () ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  target ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wcsncat (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* wusername ; 

int main(int argc, char *argv[])
{
	const char *usage =
	    "usage: git credential-wincred <get|store|erase>\n";

	if (!argv[1])
		die(usage);

	/* git use binary pipes to avoid CRLF-issues */
	_setmode(_fileno(stdin), _O_BINARY);
	_setmode(_fileno(stdout), _O_BINARY);

	read_credential();

	load_cred_funcs();

	if (!protocol || !(host || path))
		return 0;

	/* prepare 'target', the unique key for the credential */
	wcscpy(target, L"git:");
	wcsncat(target, protocol, ARRAY_SIZE(target));
	wcsncat(target, L"://", ARRAY_SIZE(target));
	if (wusername) {
		wcsncat(target, wusername, ARRAY_SIZE(target));
		wcsncat(target, L"@", ARRAY_SIZE(target));
	}
	if (host)
		wcsncat(target, host, ARRAY_SIZE(target));
	if (path) {
		wcsncat(target, L"/", ARRAY_SIZE(target));
		wcsncat(target, path, ARRAY_SIZE(target));
	}

	if (!strcmp(argv[1], "get"))
		get_credential();
	else if (!strcmp(argv[1], "store"))
		store_credential();
	else if (!strcmp(argv[1], "erase"))
		erase_credential();
	/* otherwise, ignore unknown action */
	return 0;
}