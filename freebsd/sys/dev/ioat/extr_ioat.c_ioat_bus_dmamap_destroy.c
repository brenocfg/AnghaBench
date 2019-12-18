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
struct ioat_softc {int dummy; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_log_message (int /*<<< orphan*/ ,char*,char const*,int) ; 

__attribute__((used)) static inline int
ioat_bus_dmamap_destroy(struct ioat_softc *ioat, const char *func,
    bus_dma_tag_t dmat, bus_dmamap_t map)
{
	int error;

	error = bus_dmamap_destroy(dmat, map);
	if (error != 0) {
		ioat_log_message(0,
		    "%s: bus_dmamap_destroy failed %d\n", func, error);
	}

	return (error);
}