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
struct cmx_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSR_BULK_OUT_FULL ; 
 int cmx_wait_BSR (struct cmx_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmx_write_SCR (struct cmx_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
cmx_sync_write_SCR(struct cmx_softc *sc, uint8_t val)
{
	int rv = 0;

	if ((rv = cmx_wait_BSR(sc, BSR_BULK_OUT_FULL, 0)) != 0) {
		return rv;
	}

	cmx_write_SCR(sc, val);

	if ((rv = cmx_wait_BSR(sc, BSR_BULK_OUT_FULL, 0)) != 0) {
		return rv;
	}

	return 0;
}