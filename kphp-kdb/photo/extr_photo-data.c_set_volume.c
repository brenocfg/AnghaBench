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
struct lev_photo_set_volume {int server_id; int /*<<< orphan*/  volume_id; } ;

/* Variables and functions */
 int* map_int_int_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  volumes ; 

int set_volume (struct lev_photo_set_volume *E) {
  int *t = map_int_int_add (&volumes, E->volume_id);
  if (t != NULL) {
    *t = E->server_id;
    return 1;
  }
  return 0;
}