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
typedef  int /*<<< orphan*/  seq_t ;
typedef  int /*<<< orphan*/  SCR ;
typedef  int /*<<< orphan*/  CHAR_T ;

/* Variables and functions */
 scalar_t__ F_ISSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_EX ; 
 int /*<<< orphan*/  SC_SCR_EX ; 
 int /*<<< orphan*/  SC_SCR_VI ; 
 int /*<<< orphan*/  SC_VI ; 
 int cl_pfmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t) ; 

int
cl_fmap(SCR *sp, seq_t stype, CHAR_T *from, size_t flen, CHAR_T *to, size_t tlen)
{
	/* Ignore until the screen is running, do the real work then. */
	if (F_ISSET(sp, SC_VI) && !F_ISSET(sp, SC_SCR_VI))
		return (0);
	if (F_ISSET(sp, SC_EX) && !F_ISSET(sp, SC_SCR_EX))
		return (0);

	return (cl_pfmap(sp, stype, from, flen, to, tlen));
}