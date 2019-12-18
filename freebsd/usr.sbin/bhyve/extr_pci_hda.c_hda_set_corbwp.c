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
struct hda_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hda_corb_run (struct hda_softc*) ; 

__attribute__((used)) static void
hda_set_corbwp(struct hda_softc *sc, uint32_t offset, uint32_t old)
{
	hda_corb_run(sc);
}