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
 TYPE_1__* filename_language_table ; 
 int fl_table_next ; 
 int language_unknown ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

enum language
deduce_language_from_filename (char *filename)
{
  int i;
  char *cp;

  if (filename != NULL)
    if ((cp = strrchr (filename, '.')) != NULL)
      for (i = 0; i < fl_table_next; i++)
	if (strcmp (cp, filename_language_table[i].ext) == 0)
	  return filename_language_table[i].lang;

  return language_unknown;
}