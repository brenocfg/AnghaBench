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
typedef  int /*<<< orphan*/  osm_opensm_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  osm_update_node_desc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_desc_parse(char **p_last, osm_opensm_t * p_osm, FILE * out)
{
	osm_update_node_desc(p_osm);
}