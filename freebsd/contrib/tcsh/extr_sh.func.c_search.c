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
struct wordent {struct wordent* next; struct wordent* prev; void* word; } ;
struct whyle {struct whyle* w_next; } ;
struct Strbuf {char* s; size_t len; } ;
struct Ain {scalar_t__ a_seek; scalar_t__ f_seek; scalar_t__ type; } ;
typedef  struct Strbuf Char ;

/* Variables and functions */
 int /*<<< orphan*/  Dfix1 (char*) ; 
 int /*<<< orphan*/  Gmatch (struct Strbuf*,struct Strbuf*) ; 
 void* STRNULL ; 
 struct Strbuf* STRdefault ; 
 struct Strbuf* STRthen ; 
 struct Strbuf* Sgoal ; 
 struct Strbuf Strbuf_INIT ; 
 int /*<<< orphan*/  Strbuf_cleanup (struct wordent*) ; 
 int /*<<< orphan*/  Strbuf_terminate (struct Strbuf*) ; 
 scalar_t__ Strlen (char*) ; 
 void* Strsave (char*) ; 
 int Stype ; 
 scalar_t__ TCSH_F_SEEK ; 
 int TC_BREAK ; 
 int TC_BRKSW ; 
#define  TC_CASE 138 
#define  TC_DEFAULT 137 
#define  TC_ELSE 136 
#define  TC_END 135 
#define  TC_ENDIF 134 
#define  TC_ENDSW 133 
#define  TC_FOREACH 132 
 int TC_GOTO ; 
#define  TC_IF 131 
#define  TC_LABEL 130 
#define  TC_SWITCH 129 
#define  TC_WHILE 128 
 scalar_t__ aret ; 
 int /*<<< orphan*/  bseek (struct Ain*) ; 
 int /*<<< orphan*/  cleanup_push (struct Strbuf*,int /*<<< orphan*/  (*) (struct wordent*)) ; 
 int /*<<< orphan*/  cleanup_until (struct Strbuf*) ; 
 int /*<<< orphan*/  eq (char*,struct Strbuf*) ; 
 scalar_t__ feobp ; 
 int /*<<< orphan*/  freelex (struct wordent*) ; 
 scalar_t__ fseekp ; 
 int /*<<< orphan*/  getword (struct Strbuf*) ; 
 struct wordent* histgetword (struct wordent*) ; 
 scalar_t__ intty ; 
 int /*<<< orphan*/  isrchx (int) ; 
 int /*<<< orphan*/  printprompt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  savehist (struct wordent*,int /*<<< orphan*/ ) ; 
 int srchx (char*) ; 
 struct Strbuf* strip (int /*<<< orphan*/ ) ; 
 struct whyle* whyles ; 
 int /*<<< orphan*/  wpfree (struct whyle*) ; 
 int /*<<< orphan*/  xfree (struct wordent*) ; 
 void* xmalloc (int) ; 
 int zlast ; 

__attribute__((used)) static void
search(int type, int level, Char *goal)
{
    struct Strbuf word = Strbuf_INIT;
    Char *cp;
    struct whyle *wp;
    int wlevel = 0;
    struct wordent *histent = NULL, *ohistent = NULL;

    Stype = type;
    Sgoal = goal;
    if (type == TC_GOTO) {
	struct Ain a;
	a.type = TCSH_F_SEEK;
	a.f_seek = 0;
	a.a_seek = 0;
	bseek(&a);
    }
    cleanup_push(&word, Strbuf_cleanup);
    do {
	    
	if (intty) {
	    histent = xmalloc(sizeof(*histent));
	    ohistent = xmalloc(sizeof(*histent));
	    ohistent->word = STRNULL;
	    ohistent->next = histent;
	    histent->prev = ohistent;
	}

	if (intty && fseekp == feobp && aret == TCSH_F_SEEK)
	    printprompt(1, isrchx(type == TC_BREAK ? zlast : type));
	/* xprintf("? "), flush(); */
	(void) getword(&word);
	Strbuf_terminate(&word);

	if (intty && Strlen(word.s) > 0) {
	    histent->word = Strsave(word.s);
	    histent->next = xmalloc(sizeof(*histent));
	    histent->next->prev = histent;
	    histent = histent->next;
	}

	switch (srchx(word.s)) {

	case TC_ELSE:
	    if (level == 0 && type == TC_IF)
		goto end;
	    break;

	case TC_IF:
	    while (getword(&word)) {
		if (intty) {
		    histent->word = Strsave(word.s);
		    histent->next = xmalloc(sizeof(*histent));
		    histent->next->prev = histent;
		    histent = histent->next;
		}
		continue;
	    }
	    
	    if ((type == TC_IF || type == TC_ELSE) &&
		eq(word.s, STRthen))
		level++;
	    break;

	case TC_ENDIF:
	    if (type == TC_IF || type == TC_ELSE)
		level--;
	    break;

	case TC_FOREACH:
	case TC_WHILE:
	    wlevel++;
	    if (type == TC_BREAK)
		level++;
	    break;

	case TC_END:
	    if (type == TC_BRKSW) {
		if (wlevel == 0) {
		    wp = whyles;
		    if (wp) {
			    whyles = wp->w_next;
			    wpfree(wp);
		    }
		}
	    }
	    if (type == TC_BREAK)
		level--;
	    wlevel--;
	    break;

	case TC_SWITCH:
	    if (type == TC_SWITCH || type == TC_BRKSW)
		level++;
	    break;

	case TC_ENDSW:
	    if (type == TC_SWITCH || type == TC_BRKSW)
		level--;
	    break;

	case TC_LABEL:
	    if (type == TC_GOTO && getword(&word) && eq(word.s, goal))
		level = -1;
	    break;

	default:
	    if (type != TC_GOTO && (type != TC_SWITCH || level != 0))
		break;
	    if (word.len == 0 || word.s[word.len - 1] != ':')
		break;
	    word.s[--word.len] = 0;
	    if ((type == TC_GOTO && eq(word.s, goal)) ||
		(type == TC_SWITCH && eq(word.s, STRdefault)))
		level = -1;
	    break;

	case TC_CASE:
	    if (type != TC_SWITCH || level != 0)
		break;
	    (void) getword(&word);
	    if (word.len != 0 && word.s[word.len - 1] == ':')
		word.s[--word.len] = 0;
	    cp = strip(Dfix1(word.s));
	    cleanup_push(cp, xfree);
	    if (Gmatch(goal, cp))
		level = -1;
	    cleanup_until(cp);
	    break;

	case TC_DEFAULT:
	    if (type == TC_SWITCH && level == 0)
		level = -1;
	    break;
	}
	if (intty) {
	    ohistent->prev = histgetword(histent);
	    ohistent->prev->next = ohistent;
	    savehist(ohistent, 0);
	    freelex(ohistent);
	    xfree(ohistent);
	} else 
	    (void) getword(NULL);
    } while (level >= 0);
 end:
    cleanup_until(&word);
}