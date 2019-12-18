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
typedef  int /*<<< orphan*/  uint64_t ;
struct ntb_softc {int /*<<< orphan*/  db_valid_mask; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ntb_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
intel_ntb_db_valid_mask(device_t dev)
{
	struct ntb_softc *ntb = device_get_softc(dev);

	return (ntb->db_valid_mask);
}