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
typedef  int /*<<< orphan*/ * uint32_t ;
typedef  size_t u_int ;
struct ahc_softc {int qoutfifo; int /*<<< orphan*/ * targetcmds; } ;

/* Variables and functions */

__attribute__((used)) static __inline uint32_t
ahc_targetcmd_offset(struct ahc_softc *ahc, u_int index)
{
	return (((uint8_t *)&ahc->targetcmds[index]) - ahc->qoutfifo);
}