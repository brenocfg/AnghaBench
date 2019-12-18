#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  force_reroute; } ;
struct TYPE_6__ {TYPE_1__ subn; } ;
typedef  TYPE_2__ osm_opensm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  osm_opensm_sweep (TYPE_2__*) ; 

__attribute__((used)) static void reroute_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	p_osm->subn.force_reroute = TRUE;
	osm_opensm_sweep(p_osm);
}