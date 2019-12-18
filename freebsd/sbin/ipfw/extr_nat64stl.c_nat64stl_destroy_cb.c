#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_4__ {scalar_t__ set; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ipfw_nat64stl_cfg ;
struct TYPE_5__ {scalar_t__ use_set; } ;

/* Variables and functions */
 int ESRCH ; 
 TYPE_3__ co ; 
 int /*<<< orphan*/  nat64stl_destroy (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
nat64stl_destroy_cb(ipfw_nat64stl_cfg *cfg, const char *name, uint8_t set)
{

	if (co.use_set != 0 && cfg->set != set)
		return (ESRCH);

	nat64stl_destroy(cfg->name, cfg->set);
	return (0);
}