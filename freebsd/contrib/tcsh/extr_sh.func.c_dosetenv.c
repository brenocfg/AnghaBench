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
struct command {int dummy; } ;
typedef  char Char ;

/* Variables and functions */
 int AsciiOnly ; 
 int /*<<< orphan*/  CHECK_MBYTEVAR ; 
 int /*<<< orphan*/  CTL_ESC (int) ; 
 int ERR_NAME ; 
 int ERR_VARALNUM ; 
 int ERR_VARBEGIN ; 
 int /*<<< orphan*/  G_APPEND ; 
 scalar_t__ GotTermCaps ; 
 int /*<<< orphan*/  Isprint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_MESSAGES ; 
 int MB_CUR_MAX ; 
 scalar_t__ MapsAreInited ; 
 scalar_t__ NLSMapsAreInited ; 
 int NoNLSRebind ; 
 char* STRCOLUMNS ; 
 char* STRKGROUP ; 
 char* STRKHOME ; 
 char* STRKPATH ; 
 char* STRKSHLVL ; 
 char* STRKTERM ; 
 char* STRKUSER ; 
 char* STRLANG ; 
 char* STRLINES ; 
 char* STRLSCOLORS ; 
 char* STRLS_COLORS ; 
 char* STRNLSPATH ; 
 char* STRNOREBIND ; 
 char* STRNULL ; 
 char* STRSYSTYPE ; 
 char* STRTERMCAP ; 
 int /*<<< orphan*/  STRedit ; 
 int /*<<< orphan*/  STRgroup ; 
 int /*<<< orphan*/  STRhome ; 
 int /*<<< orphan*/  STRshlvl ; 
 char* STRtcshlang ; 
 int /*<<< orphan*/  STRterm ; 
 int /*<<< orphan*/  STRuser ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  adrof (int /*<<< orphan*/ ) ; 
 scalar_t__ alnum (char) ; 
 int /*<<< orphan*/  autoset_dspmbyte (char*) ; 
 int /*<<< orphan*/  autoset_kanji () ; 
 int /*<<< orphan*/  check_window_size (int) ; 
 int /*<<< orphan*/  cleanup_ignore (char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 char* dcanon (char*,char*) ; 
 int /*<<< orphan*/  dohash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dont_free ; 
 int /*<<< orphan*/  doprintenv (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtilde () ; 
 int /*<<< orphan*/  ed_Init () ; 
 int /*<<< orphan*/  ed_InitMaps () ; 
 int /*<<< orphan*/  ed_InitNLSMaps () ; 
 int editing ; 
 scalar_t__ eq (char*,char*) ; 
 int /*<<< orphan*/  fix_strcoll_bug () ; 
 char* globone (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  importpath (char*) ; 
 scalar_t__ islocale_var (char*) ; 
 int /*<<< orphan*/  letter (char) ; 
 int /*<<< orphan*/  nlsclose () ; 
 int /*<<< orphan*/  nlsinit () ; 
 scalar_t__ noediting ; 
 int /*<<< orphan*/  parseLSCOLORS (char*) ; 
 int /*<<< orphan*/  parseLS_COLORS (char*) ; 
 int /*<<< orphan*/  quote (char*) ; 
 int /*<<< orphan*/  setNS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* short2str (char*) ; 
 int /*<<< orphan*/  stderror (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  tsetenv (char*,char*) ; 
 int /*<<< orphan*/  tw_cmd_free () ; 
 int /*<<< orphan*/  xfree ; 

void
dosetenv(Char **v, struct command *c)
{
    Char   *vp, *lp;

    USE(c);
    if (*++v == 0) {
	doprintenv(--v, 0);
	return;
    }

    vp = *v++;
    lp = vp;

    if (!letter(*lp))
	stderror(ERR_NAME | ERR_VARBEGIN);
    do {
	lp++;
    } while (alnum(*lp) || *lp == '.');
    if (*lp != '\0')
	stderror(ERR_NAME | ERR_VARALNUM);

    if ((lp = *v++) == 0)
	lp = STRNULL;

    lp = globone(lp, G_APPEND);
    cleanup_push(lp, xfree);
    tsetenv(vp, lp);
    if (eq(vp, STRKPATH)) {
        importpath(lp);
	dohash(NULL, NULL);
	cleanup_until(lp);
	return;
    }

#ifdef apollo
    if (eq(vp, STRSYSTYPE)) {
	dohash(NULL, NULL);
	cleanup_until(lp);
	return;
    }
#endif /* apollo */

    /* dspkanji/dspmbyte autosetting */
    /* PATCH IDEA FROM Issei.Suzuki VERY THANKS */
#if defined(DSPMBYTE)
    if(eq(vp, STRLANG) && !adrof(CHECK_MBYTEVAR)) {
	autoset_dspmbyte(lp);
    }
#endif

    if (islocale_var(vp)) {
#ifdef NLS
	int     k;

# ifdef SETLOCALEBUG
	dont_free = 1;
# endif /* SETLOCALEBUG */
	(void) setlocale(LC_ALL, "");
# ifdef LC_COLLATE
	(void) setlocale(LC_COLLATE, "");
# endif
# ifdef LC_CTYPE
	(void) setlocale(LC_CTYPE, ""); /* for iscntrl */
# endif /* LC_CTYPE */
# if defined(AUTOSET_KANJI)
        autoset_kanji();
# endif /* AUTOSET_KANJI */
# ifdef NLS_CATALOGS
#  ifdef LC_MESSAGES
	(void) setlocale(LC_MESSAGES, "");
#  endif /* LC_MESSAGES */
	nlsclose();
	nlsinit();
# endif /* NLS_CATALOGS */
# ifdef SETLOCALEBUG
	dont_free = 0;
# endif /* SETLOCALEBUG */
# ifdef STRCOLLBUG
	fix_strcoll_bug();
# endif /* STRCOLLBUG */
	tw_cmd_free();	/* since the collation sequence has changed */
	for (k = 0200; k <= 0377 && !Isprint(CTL_ESC(k)); k++)
	    continue;
	AsciiOnly = MB_CUR_MAX == 1 && k > 0377;
#else /* !NLS */
	AsciiOnly = 0;
#endif /* NLS */
	NLSMapsAreInited = 0;
	ed_Init();
	if (MapsAreInited && !NLSMapsAreInited)
	    ed_InitNLSMaps();
	cleanup_until(lp);
	return;
    }

#ifdef NLS_CATALOGS
    if (eq(vp, STRNLSPATH)) {
	nlsclose();
	nlsinit();
    }
#endif

    if (eq(vp, STRNOREBIND)) {
	NoNLSRebind = 1;
	MapsAreInited = 0;
	NLSMapsAreInited = 0;
	ed_InitMaps();
	cleanup_until(lp);
	return;
    }
#ifdef WINNT_NATIVE
    if (eq(vp, STRtcshlang)) {
	nlsinit();
	cleanup_until(lp);
	return;
    }
#endif /* WINNT_NATIVE */
    if (eq(vp, STRKTERM)) {
	char *t;

	setv(STRterm, quote(lp), VAR_READWRITE);	/* lp memory used here */
	cleanup_ignore(lp);
	cleanup_until(lp);
	t = short2str(lp);
	if (noediting && strcmp(t, "unknown") != 0 && strcmp(t,"dumb") != 0) {
	    editing = 1;
	    noediting = 0;
	    setNS(STRedit);
	}
	GotTermCaps = 0;
	ed_Init();
	return;
    }

    if (eq(vp, STRKHOME)) {
	Char *canon;
	/*
	 * convert to canonical pathname (possibly resolving symlinks)
	 */
	canon = dcanon(lp, lp);
	cleanup_ignore(lp);
	cleanup_until(lp);
	cleanup_push(canon, xfree);
	setv(STRhome, quote(canon), VAR_READWRITE); /* lp memory used here */
	cleanup_ignore(canon);
	cleanup_until(canon);

	/* fix directory stack for new tilde home */
	dtilde();
	return;
    }

    if (eq(vp, STRKSHLVL)) {
	setv(STRshlvl, quote(lp), VAR_READWRITE); /* lp memory used here */
	cleanup_ignore(lp);
	cleanup_until(lp);
	return;
    }

    if (eq(vp, STRKUSER)) {
	setv(STRuser, quote(lp), VAR_READWRITE);	/* lp memory used here */
	cleanup_ignore(lp);
	cleanup_until(lp);
	return;
    }

    if (eq(vp, STRKGROUP)) {
	setv(STRgroup, quote(lp), VAR_READWRITE); /* lp memory used here */
	cleanup_ignore(lp);
	cleanup_until(lp);
	return;
    }

#ifdef COLOR_LS_F
    if (eq(vp, STRLS_COLORS)) {
        parseLS_COLORS(lp);
	cleanup_until(lp);
	return;
    }
    if (eq(vp, STRLSCOLORS)) {
        parseLSCOLORS(lp);
	cleanup_until(lp);
	return;
    }
#endif /* COLOR_LS_F */

#ifdef SIG_WINDOW
    /*
     * Load/Update $LINES $COLUMNS
     */
    if ((eq(lp, STRNULL) && (eq(vp, STRLINES) || eq(vp, STRCOLUMNS))) ||
	eq(vp, STRTERMCAP)) {
	cleanup_until(lp);
	check_window_size(1);
	return;
    }

    /*
     * Change the size to the one directed by $LINES and $COLUMNS
     */
    if (eq(vp, STRLINES) || eq(vp, STRCOLUMNS)) {
#if 0
	GotTermCaps = 0;
#endif
	cleanup_until(lp);
	ed_Init();
	return;
    }
#endif /* SIG_WINDOW */
    cleanup_until(lp);
}