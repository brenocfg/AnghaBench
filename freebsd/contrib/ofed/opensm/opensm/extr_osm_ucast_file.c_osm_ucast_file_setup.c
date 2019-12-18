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
struct osm_routing_engine {int /*<<< orphan*/  ucast_build_fwd_tables; int /*<<< orphan*/  build_lid_matrices; int /*<<< orphan*/ * context; } ;
typedef  int /*<<< orphan*/  osm_opensm_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_lid_matrix_file_load ; 
 int /*<<< orphan*/  do_ucast_file_load ; 

int osm_ucast_file_setup(struct osm_routing_engine *r, osm_opensm_t *osm)
{
	r->context = osm;
	r->build_lid_matrices = do_lid_matrix_file_load;
	r->ucast_build_fwd_tables = do_ucast_file_load;
	return 0;
}