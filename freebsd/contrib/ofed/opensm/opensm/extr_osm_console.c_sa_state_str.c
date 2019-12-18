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
typedef  int osm_sa_state_t ;

/* Variables and functions */
#define  OSM_SA_STATE_INIT 129 
#define  OSM_SA_STATE_READY 128 

__attribute__((used)) static const char *sa_state_str(osm_sa_state_t state)
{
	switch (state) {
	case OSM_SA_STATE_INIT:
		return "Init";
	case OSM_SA_STATE_READY:
		return "Ready";
	}
	return "UNKNOWN";
}