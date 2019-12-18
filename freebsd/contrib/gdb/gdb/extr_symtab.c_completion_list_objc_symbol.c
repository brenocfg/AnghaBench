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
struct minimal_symbol {int dummy; } ;

/* Variables and functions */
 char* SYMBOL_NATURAL_NAME (struct minimal_symbol*) ; 
 int /*<<< orphan*/  completion_list_add_name (char*,char*,int,char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 char* xrealloc (char*,unsigned int) ; 

__attribute__((used)) static void
completion_list_objc_symbol (struct minimal_symbol *msymbol, char *sym_text,
			     int sym_text_len, char *text, char *word)
{
  static char *tmp = NULL;
  static unsigned int tmplen = 0;
    
  char *method, *category, *selector;
  char *tmp2 = NULL;
    
  method = SYMBOL_NATURAL_NAME (msymbol);

  /* Is it a method?  */
  if ((method[0] != '-') && (method[0] != '+'))
    return;

  if (sym_text[0] == '[')
    /* Complete on shortened method method.  */
    completion_list_add_name (method + 1, sym_text, sym_text_len, text, word);
    
  while ((strlen (method) + 1) >= tmplen)
    {
      if (tmplen == 0)
	tmplen = 1024;
      else
	tmplen *= 2;
      tmp = xrealloc (tmp, tmplen);
    }
  selector = strchr (method, ' ');
  if (selector != NULL)
    selector++;
    
  category = strchr (method, '(');
    
  if ((category != NULL) && (selector != NULL))
    {
      memcpy (tmp, method, (category - method));
      tmp[category - method] = ' ';
      memcpy (tmp + (category - method) + 1, selector, strlen (selector) + 1);
      completion_list_add_name (tmp, sym_text, sym_text_len, text, word);
      if (sym_text[0] == '[')
	completion_list_add_name (tmp + 1, sym_text, sym_text_len, text, word);
    }
    
  if (selector != NULL)
    {
      /* Complete on selector only.  */
      strcpy (tmp, selector);
      tmp2 = strchr (tmp, ']');
      if (tmp2 != NULL)
	*tmp2 = '\0';
	
      completion_list_add_name (tmp, sym_text, sym_text_len, text, word);
    }
}