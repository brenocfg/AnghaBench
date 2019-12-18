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
typedef  int /*<<< orphan*/  osm_qos_level_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 

osm_qos_level_t *osm_qos_policy_qos_level_create()
{
	osm_qos_level_t *p =
	    (osm_qos_level_t *) calloc(1, sizeof(osm_qos_level_t));
	return p;
}