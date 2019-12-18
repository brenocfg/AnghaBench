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
struct varent {int /*<<< orphan*/  vec; } ;
typedef  char Char ;

/* Variables and functions */
 char* CHECK_MBYTEVAR ; 
 int ERR_NAME ; 
 int ERR_UNDVAR ; 
 scalar_t__ GotTermCaps ; 
 char HIST ; 
 char HISTSUB ; 
 int HistLit ; 
 int /*<<< orphan*/  Isdigit (char) ; 
 char PRCH ; 
 char PRCHROOT ; 
 int /*<<< orphan*/  STRKGROUP ; 
 int /*<<< orphan*/  STRKHOME ; 
 int /*<<< orphan*/  STRKSHLVL ; 
 int /*<<< orphan*/  STRKTERM ; 
 int /*<<< orphan*/  STRKUSER ; 
 int /*<<< orphan*/  STRLOGNAME ; 
 int /*<<< orphan*/  STRTERMCAP ; 
 char* STRanyerror ; 
 char* STRbackslash_quote ; 
 char* STRcatalog ; 
 char* STRcdtohome ; 
 char* STRchase ; 
 char* STRcolor ; 
 char* STRcompat_expr ; 
 char* STRdirstack ; 
 int /*<<< orphan*/  STRdumb ; 
 char* STRedit ; 
 char* STRexpand ; 
 char* STRfilec ; 
 char* STRgroup ; 
 char* STRhistchars ; 
 char* STRhistlit ; 
 char* STRhistory ; 
 char* STRhome ; 
 char* STRignore ; 
 char* STRignoreeof ; 
 char* STRimplicitcd ; 
 char* STRkillring ; 
 char* STRloginsh ; 
 int /*<<< orphan*/  STRnetwork ; 
 char* STRnoclobber ; 
 char* STRnokanji ; 
 char* STRpath ; 
 char* STRpromptchars ; 
 char* STRrecognize_only_executables ; 
 char* STRshlvl ; 
 char* STRsymlinks ; 
 char* STRterm ; 
 int /*<<< orphan*/  STRunknown ; 
 char* STRuser ; 
 char* STRverbose ; 
 char* STRvimode ; 
 char* STRwatch ; 
 char* STRwordchars ; 
 scalar_t__ SYM_CHASE ; 
 scalar_t__ SYM_EXPAND ; 
 scalar_t__ SYM_IGNORE ; 
 int /*<<< orphan*/  SetKillRing (int) ; 
 scalar_t__ Strcmp (char*,int /*<<< orphan*/ ) ; 
 char* Strsave (char*) ; 
 int /*<<< orphan*/  Unsetenv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int VImode ; 
 struct varent* adrof (char*) ; 
 int anyerror ; 
 int bslash_quote ; 
 int cdtohome ; 
 int /*<<< orphan*/  cleanup_ignore (char*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int compat_expr ; 
 char* dcanon (char*,char*) ; 
 int /*<<< orphan*/  dohash (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsetstack () ; 
 int /*<<< orphan*/  dtilde () ; 
 int /*<<< orphan*/  ed_Init () ; 
 int editing ; 
 scalar_t__ eq (char*,char*) ; 
 int /*<<< orphan*/  exportpath (int /*<<< orphan*/ ) ; 
 int filec ; 
 char* getenv (char*) ; 
 scalar_t__ getn (char*) ; 
 int implicit_cd ; 
 int loginsh ; 
 int /*<<< orphan*/  nlsclose () ; 
 int /*<<< orphan*/  nlsinit () ; 
 int /*<<< orphan*/  no_clobber ; 
 scalar_t__ noediting ; 
 int numeof ; 
 int /*<<< orphan*/  resetwatch () ; 
 int /*<<< orphan*/  setNS (char*) ; 
 int /*<<< orphan*/  set_color_context () ; 
 int /*<<< orphan*/  set_noclobber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setcopy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sethistory (int) ; 
 int /*<<< orphan*/  stderror (int) ; 
 scalar_t__ symlinks ; 
 int /*<<< orphan*/  tsetenv (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cmd_free () ; 
 int /*<<< orphan*/  update_dspmbyte_vars () ; 
 int /*<<< orphan*/  update_wordchars () ; 
 char* varval (char*) ; 
 char* word_chars ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
update_vars(Char *vp)
{
    if (eq(vp, STRpath)) {
	struct varent *p = adrof(STRpath); 
	if (p == NULL)
	    stderror(ERR_NAME | ERR_UNDVAR);
	else {
	    exportpath(p->vec);
	    dohash(NULL, NULL);
	}
    }
    else if (eq(vp, STRnoclobber)) {
	struct varent *p = adrof(STRnoclobber);
	if (p == NULL)
	    stderror(ERR_NAME | ERR_UNDVAR);
	else
	    no_clobber = set_noclobber(p->vec);
    }
    else if (eq(vp, STRhistchars)) {
	Char *pn = varval(vp);

	HIST = *pn++;
	if (HIST)
	    HISTSUB = *pn;
	else
	    HISTSUB = HIST;
    }
    else if (eq(vp, STRpromptchars)) {
	Char *pn = varval(vp);

	PRCH = *pn++;
	if (PRCH)
	    PRCHROOT = *pn;
	else
	    PRCHROOT = PRCH;
    }
    else if (eq(vp, STRhistlit)) {
	HistLit = 1;
    }
    else if (eq(vp, STRuser)) {
	tsetenv(STRKUSER, varval(vp));
	tsetenv(STRLOGNAME, varval(vp));
    }
    else if (eq(vp, STRgroup)) {
	tsetenv(STRKGROUP, varval(vp));
    }
    else if (eq(vp, STRwordchars)) {
	word_chars = varval(vp);
    }
    else if (eq(vp, STRloginsh)) {
	loginsh = 1;
    }
    else if (eq(vp, STRanyerror)) {
	anyerror = 1;
    }
    else if (eq(vp, STRsymlinks)) {
	Char *pn = varval(vp);

	if (eq(pn, STRignore))
	    symlinks = SYM_IGNORE;
	else if (eq(pn, STRexpand))
	    symlinks = SYM_EXPAND;
	else if (eq(pn, STRchase))
	    symlinks = SYM_CHASE;
	else
	    symlinks = 0;
    }
    else if (eq(vp, STRterm)) {
	Char *cp = varval(vp);
	tsetenv(STRKTERM, cp);
#ifdef DOESNT_WORK_RIGHT
	cp = getenv("TERMCAP");
	if (cp && (*cp != '/'))	/* if TERMCAP and not a path */
	    Unsetenv(STRTERMCAP);
#endif /* DOESNT_WORK_RIGHT */
	GotTermCaps = 0;
	if (noediting && Strcmp(cp, STRnetwork) != 0 &&
	    Strcmp(cp, STRunknown) != 0 && Strcmp(cp, STRdumb) != 0) {
	    editing = 1;
	    noediting = 0;
	    setNS(STRedit);
	}
	ed_Init();		/* reset the editor */
    }
    else if (eq(vp, STRhome)) {
	Char *cp, *canon;

	cp = Strsave(varval(vp));	/* get the old value back */
	cleanup_push(cp, xfree);

	/*
	 * convert to cononical pathname (possibly resolving symlinks)
	 */
	canon = dcanon(cp, cp);
	cleanup_ignore(cp);
	cleanup_until(cp);
	cleanup_push(canon, xfree);

	setcopy(vp, canon, VAR_READWRITE);	/* have to save the new val */

	/* and now mirror home with HOME */
	tsetenv(STRKHOME, canon);
	/* fix directory stack for new tilde home */
	dtilde();
	cleanup_until(canon);
    }
    else if (eq(vp, STRedit)) {
	editing = 1;
	noediting = 0;
	/* PWP: add more stuff in here later */
    }
    else if (eq(vp, STRvimode)) {
	VImode = 1;
	update_wordchars();
    }
    else if (eq(vp, STRshlvl)) {
	tsetenv(STRKSHLVL, varval(vp));
    }
    else if (eq(vp, STRignoreeof)) {
	Char *cp;
	numeof = 0;
    	for ((cp = varval(STRignoreeof)); cp && *cp; cp++) {
	    if (!Isdigit(*cp)) {
		numeof = 0;
		break;
	    }
	    numeof = numeof * 10 + *cp - '0';
	}
	if (numeof <= 0) numeof = 26;	/* Sanity check */
    } 
    else if (eq(vp, STRbackslash_quote)) {
	bslash_quote = 1;
    }
    else if (eq(vp, STRcompat_expr)) {
	compat_expr = 1;
    }
    else if (eq(vp, STRdirstack)) {
	dsetstack();
    }
    else if (eq(vp, STRrecognize_only_executables)) {
	tw_cmd_free();
    }
    else if (eq(vp, STRkillring)) {
	SetKillRing((int)getn(varval(vp)));
    }
    else if (eq(vp, STRhistory)) {
	sethistory((int)getn(varval(vp)));
    }
#ifndef HAVENOUTMP
    else if (eq(vp, STRwatch)) {
	resetwatch();
    }
#endif /* HAVENOUTMP */
    else if (eq(vp, STRimplicitcd)) {
	implicit_cd = ((eq(varval(vp), STRverbose)) ? 2 : 1);
    }
    else if (eq(vp, STRcdtohome)) {
	cdtohome = 1;
    }
#ifdef COLOR_LS_F
    else if (eq(vp, STRcolor)) {
	set_color_context();
    }
#endif /* COLOR_LS_F */
#if defined(KANJI) && defined(SHORT_STRINGS) && defined(DSPMBYTE)
    else if(eq(vp, CHECK_MBYTEVAR) || eq(vp, STRnokanji)) {
	update_dspmbyte_vars();
    }
#endif
#ifdef NLS_CATALOGS
    else if (eq(vp, STRcatalog)) {
	nlsclose();
	nlsinit();
    }
#if defined(FILEC) && defined(TIOCSTI)
    else if (eq(vp, STRfilec))
	filec = 1;
#endif
#endif /* NLS_CATALOGS */
}