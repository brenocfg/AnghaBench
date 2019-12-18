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
struct general_symbol_info {scalar_t__ language; } ;

/* Variables and functions */
 int DMGL_ANSI ; 
 int DMGL_JAVA ; 
 int DMGL_PARAMS ; 
 char* cplus_demangle (char const*,int) ; 
 scalar_t__ language_auto ; 
 scalar_t__ language_cplus ; 
 scalar_t__ language_java ; 
 scalar_t__ language_objc ; 
 scalar_t__ language_unknown ; 
 char* objc_demangle (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
symbol_find_demangled_name (struct general_symbol_info *gsymbol,
			    const char *mangled)
{
  char *demangled = NULL;

  if (gsymbol->language == language_unknown)
    gsymbol->language = language_auto;

  if (gsymbol->language == language_objc
      || gsymbol->language == language_auto)
    {
      demangled =
	objc_demangle (mangled, 0);
      if (demangled != NULL)
	{
	  gsymbol->language = language_objc;
	  return demangled;
	}
    }
  if (gsymbol->language == language_cplus
      || gsymbol->language == language_auto)
    {
      demangled =
        cplus_demangle (mangled, DMGL_PARAMS | DMGL_ANSI);
      if (demangled != NULL)
	{
	  gsymbol->language = language_cplus;
	  return demangled;
	}
    }
  if (gsymbol->language == language_java)
    {
      demangled =
        cplus_demangle (mangled,
                        DMGL_PARAMS | DMGL_ANSI | DMGL_JAVA);
      if (demangled != NULL)
	{
	  gsymbol->language = language_java;
	  return demangled;
	}
    }
  return NULL;
}