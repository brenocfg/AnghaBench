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
typedef  scalar_t__ uint8_t ;
struct amd_ntb_softc {scalar_t__ spad_count; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  amd_ntb_spad_write (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
amd_ntb_spad_clear(struct amd_ntb_softc *ntb)
{
	uint8_t i;

	for (i = 0; i < ntb->spad_count; i++)
		amd_ntb_spad_write(ntb->device, i, 0);
}