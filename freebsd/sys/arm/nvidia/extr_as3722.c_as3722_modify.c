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
struct as3722_softc {int dummy; } ;

/* Variables and functions */
 int as3722_read (struct as3722_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int as3722_write (struct as3722_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
as3722_modify(struct as3722_softc *sc, uint8_t reg, uint8_t clear, uint8_t set)
{
	uint8_t val;
	int rv;

	rv = as3722_read(sc, reg, &val);
	if (rv != 0)
		return (rv);

	val &= ~clear;
	val |= set;

	rv = as3722_write(sc, reg, val);
	if (rv != 0)
		return (rv);

	return (0);
}