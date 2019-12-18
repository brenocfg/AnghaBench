#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {TYPE_2__* p_osm; } ;
typedef  TYPE_3__ osm_subn_t ;
struct TYPE_5__ {unsigned long max_size; } ;
struct TYPE_6__ {TYPE_1__ log; } ;

/* Variables and functions */

__attribute__((used)) static void opts_setup_log_max_size(osm_subn_t *p_subn, void *p_val)
{
	uint32_t log_max_size = *((uint32_t *) p_val);

	p_subn->p_osm->log.max_size = (unsigned long)log_max_size << 20; /* convert from MB to bytes */
}