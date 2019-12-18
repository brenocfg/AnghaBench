#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int high_limit; int /*<<< orphan*/ * sl2vl; int /*<<< orphan*/ * vlarb_low; int /*<<< orphan*/ * vlarb_high; scalar_t__ max_vls; } ;
typedef  TYPE_1__ osm_qos_options_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void subn_init_qos_options(osm_qos_options_t *opt, osm_qos_options_t *f)
{
	opt->max_vls = 0;
	opt->high_limit = -1;
	if (opt->vlarb_high)
		free(opt->vlarb_high);
	opt->vlarb_high = NULL;
	if (opt->vlarb_low)
		free(opt->vlarb_low);
	opt->vlarb_low = NULL;
	if (opt->sl2vl)
		free(opt->sl2vl);
	opt->sl2vl = NULL;
	if (f)
		memcpy(f, opt, sizeof(*f));
}