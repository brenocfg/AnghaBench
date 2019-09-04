#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {scalar_t__ newmode; } ;
typedef  TYPE_1__ _startupinfo ;

/* Variables and functions */
 int /*<<< orphan*/  InitializeCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CRT_glob ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/ * __argv ; 
 scalar_t__ __wgetmainargs (int*,int /*<<< orphan*/ ***,int /*<<< orphan*/ ***,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fmode ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_startup () ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc_startup (int) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  maybe_redirect_std_handles () ; 
 int /*<<< orphan*/  pinfo_cs ; 
 int /*<<< orphan*/  setup_windows_environment () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  unset_environment_variables ; 
 int wcslen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcstoutfdup_startup (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  winansi_init () ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

void mingw_startup(void)
{
	int i, maxlen, argc;
	char *buffer;
	wchar_t **wenv, **wargv;
	_startupinfo si;

	maybe_redirect_std_handles();

	/* get wide char arguments and environment */
	si.newmode = 0;
	if (__wgetmainargs(&argc, &wargv, &wenv, _CRT_glob, &si) < 0)
		die_startup();

	/* determine size of argv and environ conversion buffer */
	maxlen = wcslen(wargv[0]);
	for (i = 1; i < argc; i++)
		maxlen = max(maxlen, wcslen(wargv[i]));

	/* allocate buffer (wchar_t encodes to max 3 UTF-8 bytes) */
	maxlen = 3 * maxlen + 1;
	buffer = malloc_startup(maxlen);

	/* convert command line arguments and environment to UTF-8 */
	for (i = 0; i < argc; i++)
		__argv[i] = wcstoutfdup_startup(buffer, wargv[i], maxlen);
	free(buffer);

	/* fix Windows specific environment settings */
	setup_windows_environment();

	unset_environment_variables = xstrdup("PERL5LIB");

	/* initialize critical section for waitpid pinfo_t list */
	InitializeCriticalSection(&pinfo_cs);

	/* set up default file mode and file modes for stdin/out/err */
	_fmode = _O_BINARY;
	_setmode(_fileno(stdin), _O_BINARY);
	_setmode(_fileno(stdout), _O_BINARY);
	_setmode(_fileno(stderr), _O_BINARY);

	/* initialize Unicode console */
	winansi_init();
}