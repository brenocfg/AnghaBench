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
struct apei_resources {int /*<<< orphan*/  ioport; int /*<<< orphan*/  iomem; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void apei_resources_init(struct apei_resources *resources)
{
	INIT_LIST_HEAD(&resources->iomem);
	INIT_LIST_HEAD(&resources->ioport);
}