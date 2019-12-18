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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  al_devmap_pa ; 
 int /*<<< orphan*/  al_devmap_size ; 
 int /*<<< orphan*/  alpine_get_devmap_base (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devmap_add_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
alpine_devmap_init(platform_t plat)
{
	alpine_get_devmap_base(&al_devmap_pa, &al_devmap_size);
	devmap_add_entry(al_devmap_pa, al_devmap_size);
	return (0);
}