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
struct stm32_cryp {unsigned int authsize; TYPE_1__* areq; } ;
struct TYPE_2__ {unsigned int cryptlen; } ;

/* Variables and functions */
 scalar_t__ is_encrypt (struct stm32_cryp*) ; 

__attribute__((used)) static unsigned int stm32_cryp_get_input_text_len(struct stm32_cryp *cryp)
{
	return is_encrypt(cryp) ? cryp->areq->cryptlen :
				  cryp->areq->cryptlen - cryp->authsize;
}