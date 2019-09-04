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
struct gather {int tot_num; struct gather* saved_query; struct gather* header; TYPE_1__* List; } ;
struct TYPE_2__ {int bytes; struct gather* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct gather*) ; 
 int gather_result_memory ; 
 int /*<<< orphan*/  gathers_working ; 

void merge_delete (struct gather *G) {
  int i;
  for (i = 0; i < G->tot_num; i++) {
    if (G->List[i].bytes >= 0) {
      gather_result_memory -= G->List[i].bytes;
      free (G->List[i].data);
      G->List[i].bytes = -1;
    }
  }
  if (G->header) { free (G->header); }
  if (G->saved_query) { free (G->saved_query); }
  gathers_working --;
  free (G);
}