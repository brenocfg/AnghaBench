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
typedef  int /*<<< orphan*/  time_t ;
struct ds13rtc_softc {int /*<<< orphan*/  secaddr; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IIC_WAIT ; 
 int iicdev_readfrom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32dec (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
read_timeword(struct ds13rtc_softc *sc, time_t *secs)
{
	int err;
	uint8_t buf[4];

	if ((err = iicdev_readfrom(sc->dev, sc->secaddr, buf, sizeof(buf),
	    IIC_WAIT)) == 0)
		*secs = le32dec(buf);

	return (err);
}