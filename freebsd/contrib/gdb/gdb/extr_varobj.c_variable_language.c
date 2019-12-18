#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct varobj {TYPE_3__* root; } ;
typedef  enum varobj_languages { ____Placeholder_varobj_languages } varobj_languages ;
struct TYPE_6__ {TYPE_2__* exp; } ;
struct TYPE_5__ {TYPE_1__* language_defn; } ;
struct TYPE_4__ {int la_language; } ;

/* Variables and functions */
#define  language_c 130 
#define  language_cplus 129 
#define  language_java 128 
 int vlang_c ; 
 int vlang_cplus ; 
 int vlang_java ; 

__attribute__((used)) static enum varobj_languages
variable_language (struct varobj *var)
{
  enum varobj_languages lang;

  switch (var->root->exp->language_defn->la_language)
    {
    default:
    case language_c:
      lang = vlang_c;
      break;
    case language_cplus:
      lang = vlang_cplus;
      break;
    case language_java:
      lang = vlang_java;
      break;
    }

  return lang;
}