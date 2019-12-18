#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_1__* p_osm; } ;
typedef  TYPE_2__ osm_subn_t ;
typedef  int /*<<< orphan*/  osm_sm_t ;
struct TYPE_4__ {int /*<<< orphan*/  sm; } ;

/* Variables and functions */
 int /*<<< orphan*/  osm_set_sm_priority (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opts_setup_sm_priority(osm_subn_t *p_subn, void *p_val)
{
	osm_sm_t *p_sm = &p_subn->p_osm->sm;
	uint8_t sm_priority = *((uint8_t *) p_val);

	osm_set_sm_priority(p_sm, sm_priority);
}