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
struct regnode {int dummy; } ;
struct as3722_reg_sc {int enable_usec; } ;

/* Variables and functions */
 int as3722_reg_disable (struct as3722_reg_sc*) ; 
 int as3722_reg_enable (struct as3722_reg_sc*) ; 
 struct as3722_reg_sc* regnode_get_softc (struct regnode*) ; 

__attribute__((used)) static int
as3722_regnode_enable(struct regnode *regnode, bool val, int *udelay)
{
	struct as3722_reg_sc *sc;
	int rv;

	sc = regnode_get_softc(regnode);

	if (val)
		rv = as3722_reg_enable(sc);
	else
		rv = as3722_reg_disable(sc);
	*udelay = sc->enable_usec;
	return (rv);
}