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
struct TYPE_4__ {int /*<<< orphan*/  s; scalar_t__ len; } ;

/* Variables and functions */
 scalar_t__ Cursor ; 
 scalar_t__ F_DOWN_SEARCH_HIST ; 
 scalar_t__ F_UP_SEARCH_HIST ; 
 int /*<<< orphan*/  Hist_num ; 
 scalar_t__ InputBuf ; 
 scalar_t__ LastChar ; 
 scalar_t__ LastCmd ; 
 int /*<<< orphan*/  Strbuf_appendn (TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Strbuf_terminate (TYPE_1__*) ; 
 TYPE_1__ patbuf ; 
 int /*<<< orphan*/  xprintf (char*,int,...) ; 

__attribute__((used)) static void
c_hsetpat(void)
{
    if (LastCmd != F_UP_SEARCH_HIST && LastCmd != F_DOWN_SEARCH_HIST) {
	patbuf.len = 0;
	Strbuf_appendn(&patbuf, InputBuf, Cursor - InputBuf);
	Strbuf_terminate(&patbuf);
    }
#ifdef SDEBUG
    xprintf("\nHist_num = %d\n", Hist_num);
    xprintf("patlen = %d\n", (int)patbuf.len);
    xprintf("patbuf = \"%S\"\n", patbuf.s);
    xprintf("Cursor %d LastChar %d\n", Cursor - InputBuf, LastChar - InputBuf);
#endif
}