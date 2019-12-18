#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  mem; } ;
typedef  TYPE_1__ csa_res ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

u_int32_t
csa_readmem(csa_res *resp, u_long offset)
{
	return bus_space_read_4(rman_get_bustag(resp->mem), rman_get_bushandle(resp->mem), offset);
}