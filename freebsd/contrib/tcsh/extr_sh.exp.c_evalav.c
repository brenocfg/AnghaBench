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
struct wordent {struct wordent* next; struct wordent* prev; int /*<<< orphan*/  word; } ;
struct command {struct command* next; struct command* prev; int /*<<< orphan*/  word; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_OLD ; 
 int /*<<< orphan*/  STR0 ; 
 int /*<<< orphan*/  STRstatus ; 
 int /*<<< orphan*/  Strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VAR_READWRITE ; 
 int /*<<< orphan*/  alias (struct wordent*) ; 
 int /*<<< orphan*/  cleanup_push (struct wordent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (struct wordent*) ; 
 int /*<<< orphan*/  execute (struct wordent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initlex (struct wordent*) ; 
 int /*<<< orphan*/  lex_cleanup ; 
 int /*<<< orphan*/  setcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ seterr ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 
 struct wordent* syntax (struct wordent*,struct wordent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syntax_cleanup ; 
 struct wordent* xcalloc (int,int) ; 

__attribute__((used)) static void
evalav(Char **v)
{
    struct wordent paraml1;
    struct wordent *hp = &paraml1;
    struct command *t;
    struct wordent *wdp = hp;

    setcopy(STRstatus, STR0, VAR_READWRITE);
    initlex(hp);
    while (*v) {
	struct wordent *new = xcalloc(1, sizeof *wdp);

	new->prev = wdp;
	new->next = hp;
	wdp->next = new;
	wdp = new;
	wdp->word = Strsave(*v++);
    }
    hp->prev = wdp;
    cleanup_push(&paraml1, lex_cleanup);
    alias(&paraml1);
    t = syntax(paraml1.next, &paraml1, 0);
    cleanup_push(t, syntax_cleanup);
    if (seterr)
	stderror(ERR_OLD);
    execute(t, -1, NULL, NULL, TRUE);
    cleanup_until(&paraml1);
}