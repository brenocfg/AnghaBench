#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__** xyz; scalar_t__* smoothingGroups; } ;
typedef  TYPE_1__ picoSmoothVertices_t ;
typedef  size_t picoIndex_t ;

/* Variables and functions */

int lessSmoothVertex(void* data, picoIndex_t first, picoIndex_t second) {
	picoSmoothVertices_t* smoothVertices = data;

	if (smoothVertices->xyz[first][0] != smoothVertices->xyz[second][0]) {
		return smoothVertices->xyz[first][0] < smoothVertices->xyz[second][0];
	}
	if (smoothVertices->xyz[first][1] != smoothVertices->xyz[second][1]) {
		return smoothVertices->xyz[first][1] < smoothVertices->xyz[second][1];
	}
	if (smoothVertices->xyz[first][2] != smoothVertices->xyz[second][2]) {
		return smoothVertices->xyz[first][2] < smoothVertices->xyz[second][2];
	}
	if (smoothVertices->smoothingGroups[first] != smoothVertices->smoothingGroups[second]) {
		return smoothVertices->smoothingGroups[first] < smoothVertices->smoothingGroups[second];
	}
	return 0;
}