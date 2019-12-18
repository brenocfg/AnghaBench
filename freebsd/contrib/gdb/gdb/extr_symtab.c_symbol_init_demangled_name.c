#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct obstack {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * demangled_name; } ;
struct TYPE_4__ {TYPE_1__ cplus_specific; } ;
struct general_symbol_info {char* name; scalar_t__ language; TYPE_2__ language_specific; } ;

/* Variables and functions */
 scalar_t__ language_cplus ; 
 scalar_t__ language_java ; 
 scalar_t__ language_objc ; 
 int /*<<< orphan*/ * obsavestring (char*,int /*<<< orphan*/ ,struct obstack*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 char* symbol_find_demangled_name (struct general_symbol_info*,char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 

void
symbol_init_demangled_name (struct general_symbol_info *gsymbol,
                            struct obstack *obstack)
{
  char *mangled = gsymbol->name;
  char *demangled = NULL;

  demangled = symbol_find_demangled_name (gsymbol, mangled);
  if (gsymbol->language == language_cplus
      || gsymbol->language == language_java
      || gsymbol->language == language_objc)
    {
      if (demangled)
	{
	  gsymbol->language_specific.cplus_specific.demangled_name
	    = obsavestring (demangled, strlen (demangled), obstack);
	  xfree (demangled);
	}
      else
	gsymbol->language_specific.cplus_specific.demangled_name = NULL;
    }
  else
    {
      /* Unknown language; just clean up quietly.  */
      if (demangled)
	xfree (demangled);
    }
}