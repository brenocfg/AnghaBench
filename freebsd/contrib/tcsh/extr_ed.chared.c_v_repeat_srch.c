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
struct TYPE_2__ {int /*<<< orphan*/  s; scalar_t__ len; } ;
typedef  scalar_t__ KEYCMD ;
typedef  int /*<<< orphan*/  CCRETVAL ;

/* Variables and functions */
 int /*<<< orphan*/  CC_ERROR ; 
#define  F_DOWN_SEARCH_HIST 129 
#define  F_UP_SEARCH_HIST 128 
 int /*<<< orphan*/  InputBuf ; 
 int /*<<< orphan*/  LastChar ; 
 scalar_t__ LastCmd ; 
 int /*<<< orphan*/  e_down_search_hist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_up_search_hist (int /*<<< orphan*/ ) ; 
 TYPE_1__ patbuf ; 
 int /*<<< orphan*/  xprintf (char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CCRETVAL
v_repeat_srch(int c)
{
    CCRETVAL rv = CC_ERROR;
#ifdef SDEBUG
    xprintf("dir %d patlen %d patbuf %S\n",
	    c, (int)patbuf.len, patbuf.s);
#endif

    LastCmd = (KEYCMD) c;  /* Hack to stop c_hsetpat */
    LastChar = InputBuf;
    switch (c) {
    case F_DOWN_SEARCH_HIST:
	rv = e_down_search_hist(0);
	break;
    case F_UP_SEARCH_HIST:
	rv = e_up_search_hist(0);
	break;
    default:
	break;
    }
    return rv;
}