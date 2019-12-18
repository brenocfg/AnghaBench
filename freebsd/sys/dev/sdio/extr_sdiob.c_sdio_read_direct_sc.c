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
typedef  int /*<<< orphan*/  uint32_t ;
struct sdiob_softc {int dummy; } ;

/* Variables and functions */
 int sdiob_rw_direct_sc (struct sdiob_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sdio_read_direct_sc(struct sdiob_softc *sc, uint8_t fn, uint32_t addr,
    uint8_t *val)
{
	int error;
	uint8_t v;

	error = sdiob_rw_direct_sc(sc, fn, addr, false, &v);
	if (error == 0 && val != NULL)
		*val = v;
	return (error);
}