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
typedef  scalar_t__ wint_t ;
typedef  scalar_t__ wchar_t ;
typedef  int /*<<< orphan*/  cchar_t ;
typedef  int /*<<< orphan*/  WINDOW ;

/* Variables and functions */
 int /*<<< orphan*/  A_NORMAL ; 
 int /*<<< orphan*/  setcchar (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,short,int /*<<< orphan*/ *) ; 
 int wadd_wch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
wadd_wint(WINDOW *win, wint_t *src)
{
    cchar_t tmp;
    wchar_t wch[2];

    wch[0] = (wchar_t) (*src);
    wch[1] = 0;
    setcchar(&tmp, wch, A_NORMAL, (short) 0, NULL);
    return wadd_wch(win, &tmp);
}