#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int** insert_tags; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 int MAX_INS_TAGS ; 
 TYPE_1__* get_user (int) ; 

int get_local_id_by_random_tag (int user_id, int random_tag) {
  int i;
  user_t *U = get_user (user_id);

  if (!U || random_tag <= 0) {
    return 0;
  }
  for (i = 0; i < MAX_INS_TAGS; i++) {
    if (U->insert_tags[i][0] == random_tag) {
      return U->insert_tags[i][1];
    }
  }
  return 0;
}