#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
struct TYPE_2__ {int /*<<< orphan*/ * res; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 size_t MEMRES ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* imx6_anatop_sc ; 

uint32_t
imx6_anatop_read_4(bus_size_t offset)
{

	KASSERT(imx6_anatop_sc != NULL, ("imx6_anatop_read_4 sc NULL"));

	return (bus_read_4(imx6_anatop_sc->res[MEMRES], offset));
}