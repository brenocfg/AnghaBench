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
struct intr_irqsrc {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int al_msix_release_msi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct intr_irqsrc**) ; 

__attribute__((used)) static int
al_msix_release_msix(device_t dev, device_t child, struct intr_irqsrc *isrc)
{

	return (al_msix_release_msi(dev, child, 1, &isrc));
}