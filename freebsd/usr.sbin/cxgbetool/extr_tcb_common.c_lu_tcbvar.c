#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * aka; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ _TCBVAR ;

/* Variables and functions */
 TYPE_1__* g_tcb_info ; 
 int /*<<< orphan*/  tcb_code_err_exit (char*,char*) ; 
 scalar_t__ tcb_strmatch_nc (char*,int /*<<< orphan*/ *) ; 

_TCBVAR *
lu_tcbvar(char *name)
{
  _TCBVAR *tvp=g_tcb_info;

  while (tvp->name!=NULL) {
    if      (tcb_strmatch_nc(name,tvp->name)) return tvp;
    else if (tcb_strmatch_nc(name,tvp->aka )) return tvp;
    tvp+=1;
  }
  tcb_code_err_exit("lu_tcbvar: bad name %s\n",name);
  return NULL;
}