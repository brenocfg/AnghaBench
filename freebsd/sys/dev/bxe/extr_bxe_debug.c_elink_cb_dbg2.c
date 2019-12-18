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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  tmp ;
struct bxe_softc {int debug; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int DBG_PHY ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

void
elink_cb_dbg2(struct bxe_softc *sc,
              char             *fmt,
              uint32_t         arg1,
              uint32_t         arg2)
{
    char tmp[128], buf[128];
    if (__predict_false(sc->debug & DBG_PHY)) {
        snprintf(tmp, sizeof(tmp), "ELINK: %s", fmt);
        snprintf(buf, sizeof(buf), tmp, arg1, arg2);
        device_printf(sc->dev, "%s", buf);
    }
}