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
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int AR8216_ATU_ACTIVE ; 
 int AR8216_ATU_OP_FLUSH ; 
 int /*<<< orphan*/  AR8216_REG_ATU_FUNC0 ; 
 int ar8216_wait_bit (struct ar8xxx_priv*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar8216_atu_flush(struct ar8xxx_priv *priv)
{
	int ret;

	ret = ar8216_wait_bit(priv, AR8216_REG_ATU_FUNC0, AR8216_ATU_ACTIVE, 0);
	if (!ret)
		ar8xxx_write(priv, AR8216_REG_ATU_FUNC0, AR8216_ATU_OP_FLUSH |
							 AR8216_ATU_ACTIVE);

	return ret;
}