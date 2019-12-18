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
typedef  scalar_t__ uint32_t ;
struct scb {scalar_t__ sg_list_busaddr; scalar_t__ sg_list; } ;
struct ahd_softc {int dummy; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 scalar_t__ ahd_sg_size (struct ahd_softc*) ; 

__attribute__((used)) static __inline uint32_t
ahd_sg_virt_to_bus(struct ahd_softc *ahd, struct scb *scb, void *sg)
{
	bus_addr_t sg_offset;

	/* sg_list_phys points to entry 1, not 0 */
	sg_offset = ((uint8_t *)sg - (uint8_t *)scb->sg_list)
		  - ahd_sg_size(ahd);

	return (scb->sg_list_busaddr + sg_offset);
}