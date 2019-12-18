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
typedef  int /*<<< orphan*/  ldt ;
typedef  int /*<<< orphan*/  fixedPoint_24_8 ;
typedef  unsigned int U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int LTSIZE ; 
 int /*<<< orphan*/  RDG_fillLiteralDistrib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDG_genBlock (void*,size_t,int /*<<< orphan*/ ,double,int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void RDG_genBuffer(void* buffer, size_t size, double matchProba, double litProba, unsigned seed)
{
    U32 seed32 = seed;
    BYTE ldt[LTSIZE];
    memset(ldt, '0', sizeof(ldt));  /* yes, character '0', this is intentional */
    if (litProba<=0.0) litProba = matchProba / 4.5;
    RDG_fillLiteralDistrib(ldt, (fixedPoint_24_8)(litProba * 256 + 0.001));
    RDG_genBlock(buffer, size, 0, matchProba, ldt, &seed32);
}