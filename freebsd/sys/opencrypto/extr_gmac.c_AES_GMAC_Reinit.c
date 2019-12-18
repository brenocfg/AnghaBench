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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct aes_gmac_ctx {int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 

void
AES_GMAC_Reinit(struct aes_gmac_ctx *agc, const uint8_t *iv, uint16_t ivlen)
{

	KASSERT(ivlen <= sizeof agc->counter, ("passed ivlen too large!"));
	bcopy(iv, agc->counter, ivlen);
}