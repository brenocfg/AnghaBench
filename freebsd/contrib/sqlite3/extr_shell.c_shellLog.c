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
struct TYPE_2__ {scalar_t__ pLog; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  utf8_printf (scalar_t__,char*,int,char const*) ; 

__attribute__((used)) static void shellLog(void *pArg, int iErrCode, const char *zMsg){
  ShellState *p = (ShellState*)pArg;
  if( p->pLog==0 ) return;
  utf8_printf(p->pLog, "(%d) %s\n", iErrCode, zMsg);
  fflush(p->pLog);
}