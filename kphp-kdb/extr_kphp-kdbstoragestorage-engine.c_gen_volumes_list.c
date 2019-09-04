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
struct TYPE_2__ {int /*<<< orphan*/  volume_id; } ;

/* Variables and functions */
 int VALUE_BUFF_SIZE ; 
 TYPE_1__** Volumes ; 
 int snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 char* value_buff ; 
 int volumes ; 

int gen_volumes_list (void) {
  int i = 0;
  char *p = value_buff;
  for (i = 0; i < volumes; i++) {
    int o = value_buff + VALUE_BUFF_SIZE - p;
    if (o <= 0) {
      return -1;
    }
    int l = snprintf (p, o, i ? ",%lld" : "%lld", Volumes[i]->volume_id);
    if (l >= o) {
      return -2;
    }
    p += l;
  }
  return p - value_buff;
}