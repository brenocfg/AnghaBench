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
struct bxe_softc {int dummy; } ;
typedef  int /*<<< orphan*/  elink_log_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGI (struct bxe_softc*,char*,int /*<<< orphan*/  const) ; 

void
elink_cb_event_log(struct bxe_softc     *sc,
                   const elink_log_id_t elink_log_id,
                   ...)
{
    /* XXX */
    BLOGI(sc, "ELINK EVENT LOG (%d)\n", elink_log_id);
}