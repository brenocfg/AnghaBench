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
struct macio_chip {int flags; struct device_node* of_node; } ;
struct device_node {struct device_node* parent; } ;

/* Variables and functions */
 long ENODEV ; 
 int /*<<< orphan*/  KEYLARGO_FCR2 ; 
 int KEYLARGO_GPIO_0 ; 
 int KEYLARGO_GPIO_EXTINT_0 ; 
 int /*<<< orphan*/  KL2_CARDSEL_16 ; 
 int KL_GPIO_AIRPORT_0 ; 
 int KL_GPIO_AIRPORT_1 ; 
 int KL_GPIO_AIRPORT_2 ; 
 int KL_GPIO_AIRPORT_3 ; 
 int KL_GPIO_AIRPORT_4 ; 
 int /*<<< orphan*/  LOCK (unsigned long) ; 
 int /*<<< orphan*/  MACIO_BIC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACIO_FLAG_AIRPORT_ON ; 
 int /*<<< orphan*/  MACIO_IN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_IN8 (int) ; 
 int /*<<< orphan*/  MACIO_OUT32 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACIO_OUT8 (int,int) ; 
 int /*<<< orphan*/  UNLOCK (unsigned long) ; 
 struct macio_chip* macio_find (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static long
core99_airport_enable(struct device_node *node, long param, long value)
{
	struct macio_chip*	macio;
	unsigned long		flags;
	int			state;

	macio = macio_find(node, 0);
	if (!macio)
		return -ENODEV;

	/* Hint: we allow passing of macio itself for the sake of the
	 * sleep code
	 */
	if (node != macio->of_node &&
	    (!node->parent || node->parent != macio->of_node))
		return -ENODEV;
	state = (macio->flags & MACIO_FLAG_AIRPORT_ON) != 0;
	if (value == state)
		return 0;
	if (value) {
		/* This code is a reproduction of OF enable-cardslot
		 * and init-wireless methods, slightly hacked until
		 * I got it working.
		 */
		LOCK(flags);
		MACIO_OUT8(KEYLARGO_GPIO_0+0xf, 5);
		(void)MACIO_IN8(KEYLARGO_GPIO_0+0xf);
		UNLOCK(flags);
		mdelay(10);
		LOCK(flags);
		MACIO_OUT8(KEYLARGO_GPIO_0+0xf, 4);
		(void)MACIO_IN8(KEYLARGO_GPIO_0+0xf);
		UNLOCK(flags);

		mdelay(10);

		LOCK(flags);
		MACIO_BIC(KEYLARGO_FCR2, KL2_CARDSEL_16);
		(void)MACIO_IN32(KEYLARGO_FCR2);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_EXTINT_0+0xb, 0);
		(void)MACIO_IN8(KEYLARGO_GPIO_EXTINT_0+0xb);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_EXTINT_0+0xa, 0x28);
		(void)MACIO_IN8(KEYLARGO_GPIO_EXTINT_0+0xa);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_EXTINT_0+0xd, 0x28);
		(void)MACIO_IN8(KEYLARGO_GPIO_EXTINT_0+0xd);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_0+0xd, 0x28);
		(void)MACIO_IN8(KEYLARGO_GPIO_0+0xd);
		udelay(10);
		MACIO_OUT8(KEYLARGO_GPIO_0+0xe, 0x28);
		(void)MACIO_IN8(KEYLARGO_GPIO_0+0xe);
		UNLOCK(flags);
		udelay(10);
		MACIO_OUT32(0x1c000, 0);
		mdelay(1);
		MACIO_OUT8(0x1a3e0, 0x41);
		(void)MACIO_IN8(0x1a3e0);
		udelay(10);
		LOCK(flags);
		MACIO_BIS(KEYLARGO_FCR2, KL2_CARDSEL_16);
		(void)MACIO_IN32(KEYLARGO_FCR2);
		UNLOCK(flags);
		mdelay(100);

		macio->flags |= MACIO_FLAG_AIRPORT_ON;
	} else {
		LOCK(flags);
		MACIO_BIC(KEYLARGO_FCR2, KL2_CARDSEL_16);
		(void)MACIO_IN32(KEYLARGO_FCR2);
		MACIO_OUT8(KL_GPIO_AIRPORT_0, 0);
		MACIO_OUT8(KL_GPIO_AIRPORT_1, 0);
		MACIO_OUT8(KL_GPIO_AIRPORT_2, 0);
		MACIO_OUT8(KL_GPIO_AIRPORT_3, 0);
		MACIO_OUT8(KL_GPIO_AIRPORT_4, 0);
		(void)MACIO_IN8(KL_GPIO_AIRPORT_4);
		UNLOCK(flags);

		macio->flags &= ~MACIO_FLAG_AIRPORT_ON;
	}
	return 0;
}