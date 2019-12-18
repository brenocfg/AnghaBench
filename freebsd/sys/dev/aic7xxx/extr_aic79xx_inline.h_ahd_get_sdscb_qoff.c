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
typedef  int u_int ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_ASSERT_MODES (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AHD_MODE_CCHAN_MSK ; 
 scalar_t__ SDSCB_QOFF ; 
 int ahd_inb (struct ahd_softc*,scalar_t__) ; 

__attribute__((used)) static __inline u_int
ahd_get_sdscb_qoff(struct ahd_softc *ahd)
{
	AHD_ASSERT_MODES(ahd, AHD_MODE_CCHAN_MSK, AHD_MODE_CCHAN_MSK);
	return (ahd_inb(ahd, SDSCB_QOFF) | (ahd_inb(ahd, SDSCB_QOFF + 1) << 8));
}