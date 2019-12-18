#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  enum language { ____Placeholder_language } language ;
struct TYPE_2__ {int lang; int /*<<< orphan*/  ext; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_filename_language (char*,int) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 char* ext_args ; 
 TYPE_1__* filename_language_table ; 
 int fl_table_next ; 
 scalar_t__ isspace (char) ; 
 int language_enum (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void
set_ext_lang_command (char *args, int from_tty)
{
  int i;
  char *cp = ext_args;
  enum language lang;

  /* First arg is filename extension, starting with '.' */
  if (*cp != '.')
    error ("'%s': Filename extension must begin with '.'", ext_args);

  /* Find end of first arg.  */
  while (*cp && !isspace (*cp))
    cp++;

  if (*cp == '\0')
    error ("'%s': two arguments required -- filename extension and language",
	   ext_args);

  /* Null-terminate first arg */
  *cp++ = '\0';

  /* Find beginning of second arg, which should be a source language.  */
  while (*cp && isspace (*cp))
    cp++;

  if (*cp == '\0')
    error ("'%s': two arguments required -- filename extension and language",
	   ext_args);

  /* Lookup the language from among those we know.  */
  lang = language_enum (cp);

  /* Now lookup the filename extension: do we already know it?  */
  for (i = 0; i < fl_table_next; i++)
    if (0 == strcmp (ext_args, filename_language_table[i].ext))
      break;

  if (i >= fl_table_next)
    {
      /* new file extension */
      add_filename_language (ext_args, lang);
    }
  else
    {
      /* redefining a previously known filename extension */

      /* if (from_tty) */
      /*   query ("Really make files of type %s '%s'?", */
      /*          ext_args, language_str (lang));           */

      xfree (filename_language_table[i].ext);
      filename_language_table[i].ext = xstrdup (ext_args);
      filename_language_table[i].lang = lang;
    }
}