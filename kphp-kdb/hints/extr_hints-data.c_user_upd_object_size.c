#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int currId; } ;
struct TYPE_5__ {int object_size; void* object_ratings; void* object_names; TYPE_1__ object_table; } ;
typedef  TYPE_2__ user ;
typedef  int /*<<< orphan*/  rating ;

/* Variables and functions */
 void* dl_realloc (void*,int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int rating_num ; 

void user_upd_object_size (user *u) {
  if (u->object_table.currId >= u->object_size) {
    int len = u->object_size;

    u->object_size = u->object_table.currId * 2;
#ifdef HINTS
    u->object_names = dl_realloc (u->object_names, sizeof (char *) * u->object_size, sizeof (char *) * len);
    memset (u->object_names + len, 0, sizeof (char *) * (u->object_size - len));
#endif

    u->object_ratings = dl_realloc (u->object_ratings, sizeof (rating) * u->object_size * rating_num, sizeof (rating) * len * rating_num);
    memset (u->object_ratings + len * rating_num, 0, sizeof (rating) * (u->object_size - len) * rating_num);
  }
}