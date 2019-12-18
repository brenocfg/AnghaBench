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
typedef  int uint32_t ;
typedef  size_t u_int ;
struct ahd_softc {scalar_t__ qoutfifo; int /*<<< orphan*/ * targetcmds; } ;

/* Variables and functions */

__attribute__((used)) static __inline uint32_t
ahd_targetcmd_offset(struct ahd_softc *ahd, u_int index)
{
	return (((uint8_t *)&ahd->targetcmds[index])
	       - (uint8_t *)ahd->qoutfifo);
}