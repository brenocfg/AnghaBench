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
struct varobj {TYPE_2__* root; } ;
struct TYPE_4__ {TYPE_1__* lang; } ;
struct TYPE_3__ {char* (* name_of_variable ) (struct varobj*) ;} ;

/* Variables and functions */
 char* stub1 (struct varobj*) ; 

__attribute__((used)) static char *
name_of_variable (struct varobj *var)
{
  return (*var->root->lang->name_of_variable) (var);
}