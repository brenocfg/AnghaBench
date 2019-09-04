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
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int MAX_TYPE ; 
 int /*<<< orphan*/  debug (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* debug_buff ; 
 char* ds ; 
 int /*<<< orphan*/ * type_size ; 
 TYPE_1__* types ; 

char *get_type_size (int type) {
  int first, last;
  if (type == -1) {
    first = 1;
    last = MAX_TYPE;
  } else if (1 <= type && type < MAX_TYPE) {
    first = type;
    last = type + 1;
  } else {
    return "";
  }

  ds = debug_buff;

  int i;
  for (i = first; i < last; i++) {
    if (types[i].name != NULL) {
      debug ("[%40s](%5d) : %9lld\n", types[i].name, i, type_size[i]);
    }
  }

  *ds = 0;
  return debug_buff;
}