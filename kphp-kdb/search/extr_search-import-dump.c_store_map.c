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

/* Variables and functions */
 int MAP_SIZE ; 
 int* Map ; 
 int /*<<< orphan*/  map_changes ; 
 int map_size ; 

void store_map (int x, int v) {
  if (x <= 0 || x >= MAP_SIZE) { return; }
  if (x >= map_size) { map_size = x + 1; }
  Map[x] = v;
  map_changes++;
}