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

/* Variables and functions */
 int /*<<< orphan*/  IPI_HASHFIELDS_NONE ; 
 int /*<<< orphan*/  V_divcb ; 
 int /*<<< orphan*/  V_divcbinfo ; 
 int /*<<< orphan*/  div_inpcb_init ; 
 int /*<<< orphan*/  in_pcbinfo_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
div_init(void)
{

	/*
	 * XXX We don't use the hash list for divert IP, but it's easier to
	 * allocate one-entry hash lists than it is to check all over the
	 * place for hashbase == NULL.
	 */
	in_pcbinfo_init(&V_divcbinfo, "div", &V_divcb, 1, 1, "divcb",
	    div_inpcb_init, IPI_HASHFIELDS_NONE);
}