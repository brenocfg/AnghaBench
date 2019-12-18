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
struct time_regs {int dummy; } ;
struct ds13rtc_softc {int /*<<< orphan*/  secaddr; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_WAIT ; 
 int iicdev_readfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct time_regs*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
read_timeregs(struct ds13rtc_softc *sc, struct time_regs *tregs)
{
	int err;

	if ((err = iicdev_readfrom(sc->dev, sc->secaddr, tregs,
	    sizeof(*tregs), IIC_WAIT)) != 0)
		return (err);

	return (err);
}