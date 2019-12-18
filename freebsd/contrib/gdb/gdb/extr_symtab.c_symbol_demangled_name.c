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
struct TYPE_3__ {char* demangled_name; } ;
struct TYPE_4__ {TYPE_1__ cplus_specific; } ;
struct general_symbol_info {scalar_t__ language; TYPE_2__ language_specific; } ;

/* Variables and functions */
 scalar_t__ language_cplus ; 
 scalar_t__ language_java ; 
 scalar_t__ language_objc ; 

char *
symbol_demangled_name (struct general_symbol_info *gsymbol)
{
  if (gsymbol->language == language_cplus
      || gsymbol->language == language_java
      || gsymbol->language == language_objc)
    return gsymbol->language_specific.cplus_specific.demangled_name;

  else 
    return NULL;
}