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
struct ioat_softc {int dummy; } ;
struct ioat_descriptor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IOAT ; 
 int /*<<< orphan*/  free_domain (struct ioat_descriptor*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ioat_free_ring(struct ioat_softc *ioat, uint32_t size,
    struct ioat_descriptor *ring)
{

	free_domain(ring, M_IOAT);
}