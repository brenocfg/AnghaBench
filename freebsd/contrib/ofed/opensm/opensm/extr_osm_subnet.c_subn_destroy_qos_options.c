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
struct TYPE_3__ {int /*<<< orphan*/  sl2vl; int /*<<< orphan*/  vlarb_low; int /*<<< orphan*/  vlarb_high; } ;
typedef  TYPE_1__ osm_qos_options_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void subn_destroy_qos_options(osm_qos_options_t *opt)
{
	free(opt->vlarb_high);
	free(opt->vlarb_low);
	free(opt->sl2vl);
}