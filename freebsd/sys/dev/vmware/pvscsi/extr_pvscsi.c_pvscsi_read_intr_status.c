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
struct pvscsi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVSCSI_REG_OFFSET_INTR_STATUS ; 
 int /*<<< orphan*/  pvscsi_reg_read (struct pvscsi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t
pvscsi_read_intr_status(struct pvscsi_softc *sc)
{

	return (pvscsi_reg_read(sc, PVSCSI_REG_OFFSET_INTR_STATUS));
}