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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 char HIST ; 
 char HISTSUB ; 
 scalar_t__ HistLit ; 
 char PRCH ; 
 char PRCHROOT ; 
 int /*<<< orphan*/  STR_WORD_CHARS ; 
 int /*<<< orphan*/  STRanyerror ; 
 int /*<<< orphan*/  STRbackslash_quote ; 
 int /*<<< orphan*/  STRcdtohome ; 
 int /*<<< orphan*/  STRcolor ; 
 int /*<<< orphan*/  STRcompat_expr ; 
 int /*<<< orphan*/  STRedit ; 
 int /*<<< orphan*/  STRfilec ; 
 int /*<<< orphan*/  STRhistchars ; 
 int /*<<< orphan*/  STRhistlit ; 
 int /*<<< orphan*/  STRhistory ; 
 int /*<<< orphan*/  STRignoreeof ; 
 int /*<<< orphan*/  STRimplicitcd ; 
 int /*<<< orphan*/  STRkillring ; 
 int /*<<< orphan*/  STRloginsh ; 
 int /*<<< orphan*/  STRnoclobber ; 
 int /*<<< orphan*/  STRpromptchars ; 
 int /*<<< orphan*/  STRrecognize_only_executables ; 
 int /*<<< orphan*/  STRsymlinks ; 
 int /*<<< orphan*/  STRvimode ; 
 int /*<<< orphan*/  STRwordchars ; 
 int /*<<< orphan*/  SetKillRing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 scalar_t__ VImode ; 
 int /*<<< orphan*/ * adrof (int /*<<< orphan*/ ) ; 
 scalar_t__ anyerror ; 
 scalar_t__ bslash_quote ; 
 scalar_t__ cdtohome ; 
 scalar_t__ compat_expr ; 
 scalar_t__ editing ; 
 scalar_t__ filec ; 
 scalar_t__ implicit_cd ; 
 scalar_t__ loginsh ; 
 int /*<<< orphan*/  nlsclose () ; 
 int /*<<< orphan*/  nlsinit () ; 
 scalar_t__ no_clobber ; 
 scalar_t__ noediting ; 
 scalar_t__ numeof ; 
 int /*<<< orphan*/  set_color_context () ; 
 int /*<<< orphan*/  sethistory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shvhed ; 
 scalar_t__ symlinks ; 
 scalar_t__ tcsh ; 
 int /*<<< orphan*/  tw_cmd_free () ; 
 int /*<<< orphan*/  unset1 (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_dspmbyte_vars () ; 
 int /*<<< orphan*/  update_wordchars () ; 
 int /*<<< orphan*/  word_chars ; 

void
unset(Char **v, struct command *c)
{
    int did_roe, did_edit;

    USE(c);
    did_roe = adrof(STRrecognize_only_executables) != NULL;
    did_edit = adrof(STRedit) != NULL;
    unset1(v, &shvhed);

#if defined(FILEC) && defined(TIOCSTI)
    if (adrof(STRfilec) == 0)
	filec = 0;
#endif /* FILEC && TIOCSTI */

    if (adrof(STRhistchars) == 0) {
	HIST = '!';
	HISTSUB = '^';
    }
    if (adrof(STRignoreeof) == 0)
	numeof = 0;
    if (adrof(STRpromptchars) == 0) {
	PRCH = tcsh ? '>' : '%';
	PRCHROOT = '#';
    }
    if (adrof(STRnoclobber) == 0)
	no_clobber = 0;
    if (adrof(STRhistlit) == 0)
	HistLit = 0;
    if (adrof(STRloginsh) == 0)
	loginsh = 0;
    if (adrof(STRanyerror) == 0)
	anyerror = 0;
    if (adrof(STRwordchars) == 0)
	word_chars = STR_WORD_CHARS;
    if (adrof(STRedit) == 0)
	editing = 0;
    if (adrof(STRbackslash_quote) == 0)
	bslash_quote = 0;
    if (adrof(STRcompat_expr) == 0)
	compat_expr = 0;
    if (adrof(STRsymlinks) == 0)
	symlinks = 0;
    if (adrof(STRimplicitcd) == 0)
	implicit_cd = 0;
    if (adrof(STRcdtohome) == 0)
	cdtohome = 0;
    if (adrof(STRkillring) == 0)
	SetKillRing(0);
    if (did_edit && noediting && adrof(STRedit) == 0)
	noediting = 0;
    if (adrof(STRvimode) == 0)
	VImode = 0;
    if (did_roe && adrof(STRrecognize_only_executables) == 0)
	tw_cmd_free();
    if (adrof(STRhistory) == 0)
	sethistory(0);
#ifdef COLOR_LS_F
    if (adrof(STRcolor) == 0)
	set_color_context();
#endif /* COLOR_LS_F */
#if defined(KANJI) && defined(SHORT_STRINGS) && defined(DSPMBYTE)
    update_dspmbyte_vars();
#endif
    update_wordchars();
#ifdef NLS_CATALOGS
    nlsclose();
    nlsinit();
#endif /* NLS_CATALOGS */
}