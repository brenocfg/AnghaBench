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
 int /*<<< orphan*/  CODESET ; 
 int /*<<< orphan*/  MCLoadBySet ; 
 int /*<<< orphan*/  NL_CAT_LOCALE ; 
 int /*<<< orphan*/  STRLC_MESSAGES ; 
 int /*<<< orphan*/  STRcatalog ; 
 int /*<<< orphan*/ * adrof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  catd ; 
 int /*<<< orphan*/  catgets_iconv ; 
 int /*<<< orphan*/  catopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dateinit () ; 
 int /*<<< orphan*/  editinit () ; 
 int /*<<< orphan*/  errinit () ; 
 int /*<<< orphan*/  iconv_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesginit () ; 
 int /*<<< orphan*/  nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nls_dll_init () ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  terminit () ; 
 scalar_t__ tgetenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  varval (int /*<<< orphan*/ ) ; 
 char* xasprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcatgets (int /*<<< orphan*/ ,int,int,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
nlsinit(void)
{
#ifdef NLS_CATALOGS
    static const char default_catalog[] = "tcsh";

    char *catalog = (char *)(intptr_t)default_catalog;

    if (adrof(STRcatalog) != NULL)
	catalog = xasprintf("tcsh.%s", short2str(varval(STRcatalog)));
#ifdef NL_CAT_LOCALE /* POSIX-compliant. */
    /*
     * Check if LC_MESSAGES is set in the environment and use it, if so.
     * If not, fall back to the setting of LANG.
     */
    catd = catopen(catalog, tgetenv(STRLC_MESSAGES) ? NL_CAT_LOCALE : 0);
#else /* pre-POSIX */
# ifndef MCLoadBySet
#  define MCLoadBySet 0
#  endif
    catd = catopen(catalog, MCLoadBySet);
#endif
    if (catalog != default_catalog)
	xfree(catalog);
#if defined(HAVE_ICONV) && defined(HAVE_NL_LANGINFO)
    /* xcatgets (), not CGETS, the charset name should be in ASCII anyway. */
    catgets_iconv = iconv_open (nl_langinfo (CODESET),
				xcatgets(catd, 255, 1, "UTF-8"));
#endif /* HAVE_ICONV && HAVE_NL_LANGINFO */
#endif /* NLS_CATALOGS */
#ifdef WINNT_NATIVE
    nls_dll_init();
#endif /* WINNT_NATIVE */
    errinit();		/* init the errorlist in correct locale */
    mesginit();		/* init the messages for signals */
    dateinit();		/* init the messages for dates */
    editinit();		/* init the editor messages */
    terminit();		/* init the termcap messages */
}