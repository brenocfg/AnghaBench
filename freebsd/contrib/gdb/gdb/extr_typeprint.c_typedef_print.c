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
struct ui_file {int dummy; } ;
struct type {int dummy; } ;
struct symbol {int dummy; } ;
struct TYPE_2__ {int la_language; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_PRINT_NAME (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 int /*<<< orphan*/  TYPE_NAME (int /*<<< orphan*/ ) ; 
 TYPE_1__* current_language ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,...) ; 
#define  language_c 131 
#define  language_cplus 130 
#define  language_m2 129 
#define  language_pascal 128 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_print (struct type*,char*,struct ui_file*,int /*<<< orphan*/ ) ; 

void
typedef_print (struct type *type, struct symbol *new, struct ui_file *stream)
{
  CHECK_TYPEDEF (type);
  switch (current_language->la_language)
    {
#ifdef _LANG_c
    case language_c:
    case language_cplus:
      fprintf_filtered (stream, "typedef ");
      type_print (type, "", stream, 0);
      if (TYPE_NAME ((SYMBOL_TYPE (new))) == 0
	  || strcmp (TYPE_NAME ((SYMBOL_TYPE (new))), DEPRECATED_SYMBOL_NAME (new)) != 0)
	fprintf_filtered (stream, " %s", SYMBOL_PRINT_NAME (new));
      break;
#endif
#ifdef _LANG_m2
    case language_m2:
      fprintf_filtered (stream, "TYPE ");
      if (!TYPE_NAME (SYMBOL_TYPE (new))
	  || strcmp (TYPE_NAME ((SYMBOL_TYPE (new))), DEPRECATED_SYMBOL_NAME (new)) != 0)
	fprintf_filtered (stream, "%s = ", SYMBOL_PRINT_NAME (new));
      else
	fprintf_filtered (stream, "<builtin> = ");
      type_print (type, "", stream, 0);
      break;
#endif
#ifdef _LANG_pascal
    case language_pascal:
      fprintf_filtered (stream, "type ");
      fprintf_filtered (stream, "%s = ", SYMBOL_PRINT_NAME (new));
      type_print (type, "", stream, 0);
      break;
#endif
    default:
      error ("Language not supported.");
    }
  fprintf_filtered (stream, ";\n");
}