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
struct TYPE_2__ {scalar_t__ nProgress; scalar_t__ mxProgress; int flgProgress; int /*<<< orphan*/  out; } ;
typedef  TYPE_1__ ShellState ;

/* Variables and functions */
 int SHELL_PROGRESS_ONCE ; 
 int SHELL_PROGRESS_QUIET ; 
 int SHELL_PROGRESS_RESET ; 
 int /*<<< orphan*/  raw_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int progress_handler(void *pClientData) {
  ShellState *p = (ShellState*)pClientData;
  p->nProgress++;
  if( p->nProgress>=p->mxProgress && p->mxProgress>0 ){
    raw_printf(p->out, "Progress limit reached (%u)\n", p->nProgress);
    if( p->flgProgress & SHELL_PROGRESS_RESET ) p->nProgress = 0;
    if( p->flgProgress & SHELL_PROGRESS_ONCE ) p->mxProgress = 0;
    return 1;
  }
  if( (p->flgProgress & SHELL_PROGRESS_QUIET)==0 ){
    raw_printf(p->out, "Progress %u\n", p->nProgress);
  }
  return 0;
}