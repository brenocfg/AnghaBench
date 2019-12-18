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
 char r_str (struct ppc_data*) ; 
 int /*<<< orphan*/  w_str (struct ppc_data*,char) ; 

__attribute__((used)) static void
ppc_reset_epp_timeout(struct ppc_data *ppc)
{
	char r;

	r = r_str(ppc);
	w_str(ppc, r | 0x1);
	w_str(ppc, r & 0xfe);

	return;
}