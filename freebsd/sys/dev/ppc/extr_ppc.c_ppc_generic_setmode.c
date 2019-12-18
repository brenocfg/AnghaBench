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
typedef  int /*<<< orphan*/  u_char ;
struct ppc_data {int ppc_avm; int ppc_dtm; int ppc_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 int PPB_ECP ; 
 int PPB_EPP ; 
 int PPB_PS2 ; 
 int /*<<< orphan*/  PPC_DISABLE_INTR ; 
 int /*<<< orphan*/  PPC_ECR_ECP ; 
 int /*<<< orphan*/  PPC_ECR_PS2 ; 
 int /*<<< orphan*/  PPC_ECR_RESET ; 
 int /*<<< orphan*/  PPC_ECR_STD ; 
 int /*<<< orphan*/  w_ecr (struct ppc_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ppc_generic_setmode(struct ppc_data *ppc, int mode)
{
	u_char ecr = 0;

	/* check if mode is available */
	if (mode && !(ppc->ppc_avm & mode))
		return (EINVAL);

	/* if ECP mode, configure ecr register */
	if ((ppc->ppc_avm & PPB_ECP) || (ppc->ppc_dtm & PPB_ECP)) {
		/* return to byte mode (keeping direction bit),
		 * no interrupt, no DMA to be able to change to
		 * ECP
		 */
		w_ecr(ppc, PPC_ECR_RESET);
		ecr = PPC_DISABLE_INTR;

		if (mode & PPB_EPP)
			return (EINVAL);
		else if (mode & PPB_ECP)
			/* select ECP mode */
			ecr |= PPC_ECR_ECP;
		else if (mode & PPB_PS2)
			/* select PS2 mode with ECP */
			ecr |= PPC_ECR_PS2;
		else
			/* select COMPATIBLE/NIBBLE mode */
			ecr |= PPC_ECR_STD;

		w_ecr(ppc, ecr);
	}

	ppc->ppc_mode = mode;

	return (0);
}