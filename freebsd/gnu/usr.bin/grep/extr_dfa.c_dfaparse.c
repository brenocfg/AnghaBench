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
struct dfa {scalar_t__ nregexps; int /*<<< orphan*/  depth; } ;
typedef  int /*<<< orphan*/  mbstate_t ;

/* Variables and functions */
 scalar_t__ CAT ; 
 scalar_t__ END ; 
 int /*<<< orphan*/  LC_COLLATE ; 
 int MB_CUR_MAX ; 
 scalar_t__ ORTOP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  addtok (scalar_t__) ; 
 scalar_t__ cur_mb_index ; 
 scalar_t__ cur_mb_len ; 
 int /*<<< orphan*/  depth ; 
 struct dfa* dfa ; 
 int /*<<< orphan*/  dfaerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hard_LC_COLLATE ; 
 int /*<<< orphan*/  hard_locale (int /*<<< orphan*/ ) ; 
 int laststart ; 
 scalar_t__ lasttok ; 
 scalar_t__ lex () ; 
 size_t lexleft ; 
 char const* lexptr ; 
 char const* lexstart ; 
 int /*<<< orphan*/  mbs ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parens ; 
 int /*<<< orphan*/  regexp (int) ; 
 int /*<<< orphan*/  syntax_bits_set ; 
 scalar_t__ tok ; 

void
dfaparse (char const *s, size_t len, struct dfa *d)
{
  dfa = d;
  lexstart = lexptr = s;
  lexleft = len;
  lasttok = END;
  laststart = 1;
  parens = 0;
  hard_LC_COLLATE = hard_locale (LC_COLLATE);
#ifdef MBS_SUPPORT
  if (MB_CUR_MAX > 1)
    {
      cur_mb_index = 0;
      cur_mb_len = 0;
      memset(&mbs, 0, sizeof(mbstate_t));
    }
#endif /* MBS_SUPPORT  */

  if (! syntax_bits_set)
    dfaerror(_("No syntax specified"));

  tok = lex();
  depth = d->depth;

  regexp(1);

  if (tok != END)
    dfaerror(_("Unbalanced )"));

  addtok(END - d->nregexps);
  addtok(CAT);

  if (d->nregexps)
    addtok(ORTOP);

  ++d->nregexps;
}