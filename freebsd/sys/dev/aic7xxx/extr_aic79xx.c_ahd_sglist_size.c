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
struct ahd_softc {int flags; } ;
struct ahd_dma_seg {int dummy; } ;
struct ahd_dma64_seg {int dummy; } ;
typedef  int bus_size_t ;

/* Variables and functions */
 int AHD_64BIT_ADDRESSING ; 
 int AHD_NSEG ; 

__attribute__((used)) static u_int
ahd_sglist_size(struct ahd_softc *ahd)
{
	bus_size_t list_size;

	list_size = sizeof(struct ahd_dma_seg) * AHD_NSEG;
	if ((ahd->flags & AHD_64BIT_ADDRESSING) != 0)
		list_size = sizeof(struct ahd_dma64_seg) * AHD_NSEG;
	return (list_size);
}