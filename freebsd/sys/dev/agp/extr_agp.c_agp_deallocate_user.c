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
struct agp_memory {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_FREE_MEMORY (int /*<<< orphan*/ ,struct agp_memory*) ; 
 int ENOENT ; 
 struct agp_memory* agp_find_memory (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
agp_deallocate_user(device_t dev, int id)
{
	struct agp_memory *mem = agp_find_memory(dev, id);

	if (mem) {
		AGP_FREE_MEMORY(dev, mem);
		return 0;
	} else {
		return ENOENT;
	}
}