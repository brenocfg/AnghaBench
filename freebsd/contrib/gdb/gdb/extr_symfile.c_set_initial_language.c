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
struct partial_symtab {int /*<<< orphan*/ * filename; } ;
typedef  enum language { ____Placeholder_language } language ;

/* Variables and functions */
 int /*<<< orphan*/  current_language ; 
 int deduce_language_from_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expected_language ; 
 struct partial_symtab* find_main_psymtab () ; 
 int language_c ; 
 int language_unknown ; 
 int /*<<< orphan*/  set_language (int) ; 

__attribute__((used)) static void
set_initial_language (void)
{
  struct partial_symtab *pst;
  enum language lang = language_unknown;

  pst = find_main_psymtab ();
  if (pst != NULL)
    {
      if (pst->filename != NULL)
	{
	  lang = deduce_language_from_filename (pst->filename);
	}
      if (lang == language_unknown)
	{
	  /* Make C the default language */
	  lang = language_c;
	}
      set_language (lang);
      expected_language = current_language;	/* Don't warn the user */
    }
}