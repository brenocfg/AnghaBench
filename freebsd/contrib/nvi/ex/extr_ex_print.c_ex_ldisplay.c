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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 int /*<<< orphan*/  E_C_LIST ; 
 int /*<<< orphan*/  INTERRUPTED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * L (char*) ; 
 scalar_t__ LF_ISSET (int /*<<< orphan*/ ) ; 
 scalar_t__ ex_prchars (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ex_puts (int /*<<< orphan*/ *,char*) ; 

int
ex_ldisplay(SCR *sp, const CHAR_T *p, size_t len, size_t col, u_int flags)
{
	if (len > 0 && ex_prchars(sp, p, &col, len, LF_ISSET(E_C_LIST), 0))
		return (1);
	if (!INTERRUPTED(sp) && LF_ISSET(E_C_LIST)) {
		p = L("$");
		if (ex_prchars(sp, p, &col, 1, LF_ISSET(E_C_LIST), 0))
			return (1);
	}
	if (!INTERRUPTED(sp))
		(void)ex_puts(sp, "\n");
	return (0);
}