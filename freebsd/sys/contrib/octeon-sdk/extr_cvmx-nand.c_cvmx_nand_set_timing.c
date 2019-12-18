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
typedef  int /*<<< orphan*/  cvmx_nand_status_t ;
struct TYPE_2__ {int tim_mult; int* tim_par; int* clen; int* alen; int* rdn; int* wrn; int /*<<< orphan*/  page_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_NAND_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_NAND_LOG_CALLED () ; 
 int /*<<< orphan*/  CVMX_NAND_RETURN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_NAND_SUCCESS ; 
 TYPE_1__* cvmx_nand_state ; 

cvmx_nand_status_t cvmx_nand_set_timing(int chip, int tim_mult, int tim_par[8], int clen[4], int alen[4], int rdn[4], int wrn[2])
{
    int i;
    CVMX_NAND_LOG_CALLED();

    if ((chip < 0) || (chip > 7))
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);
    if (!cvmx_nand_state[chip].page_size)
        CVMX_NAND_RETURN(CVMX_NAND_INVALID_PARAM);

    cvmx_nand_state[chip].tim_mult = tim_mult;
    for (i=0;i<8;i++)
        cvmx_nand_state[chip].tim_par[i] = tim_par[i];
    for (i=0;i<4;i++)
        cvmx_nand_state[chip].clen[i] = clen[i];
    for (i=0;i<4;i++)
        cvmx_nand_state[chip].alen[i] = alen[i];
    for (i=0;i<4;i++)
        cvmx_nand_state[chip].rdn[i] = rdn[i];
    for (i=0;i<2;i++)
        cvmx_nand_state[chip].wrn[i] = wrn[i];

    CVMX_NAND_RETURN(CVMX_NAND_SUCCESS);
}