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
struct ppc_data {int dummy; } ;

/* Variables and functions */
 int r_dtr (struct ppc_data*) ; 
 int /*<<< orphan*/  w_ctr (struct ppc_data*,int) ; 
 int /*<<< orphan*/  w_dtr (struct ppc_data*,int) ; 

__attribute__((used)) static int
ppc_detect_port(struct ppc_data *ppc)
{

	w_ctr(ppc, 0x0c);	/* To avoid missing PS2 ports */
	w_dtr(ppc, 0xaa);
	if (r_dtr(ppc) != 0xaa)
		return (0);

	return (1);
}