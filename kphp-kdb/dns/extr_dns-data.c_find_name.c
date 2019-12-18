#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int child_node_id; } ;
struct TYPE_3__ {int zone_id; } ;

/* Variables and functions */
 TYPE_2__* edge_buff ; 
 int get_name_f (char const*,int,int /*<<< orphan*/ ) ; 
 int get_node_f (int,char const*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* names ; 

__attribute__((used)) static int find_name (const char *name, int l, int *name_id, int *zone_id) {
  *name_id = get_name_f (name, l, 0);
  if (*name_id < 0) {
    /* try to find *.<domain> */
    int parent_node_id = -1;
    while (l > 0) {
      int i;
      for (i = l - 1; i >= 0 && name[i] != '.'; i--) { }
      //label = name[i+1:l]
      const int star_name_id = get_node_f (parent_node_id, "*", 1, 0);
      if (star_name_id >= 0) {
        *name_id = star_name_id;
      }
      const int node_id = get_node_f (parent_node_id, name + i + 1, (l - (i + 1)), 0);
      if (node_id < 0) {
        break;
      }
      l = i;
      parent_node_id = edge_buff[node_id].child_node_id;
    }
    if (*name_id < 0) {
      *zone_id = parent_node_id >= 0 ? names[parent_node_id].zone_id : -1;
      return -1;
    }
  }
  *zone_id = names[*name_id].zone_id;
  return 0;
}