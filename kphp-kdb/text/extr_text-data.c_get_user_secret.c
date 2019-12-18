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
struct TYPE_3__ {char* secret; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 TYPE_1__* get_user (int) ; 

char *get_user_secret (int user_id) {
  user_t *U = get_user (user_id);
  int i;

  if (!U) {
    return 0;
  }

  for (i = 0; i < 8; i++) {
    if (U->secret[i]) {
      break;
    }
  }

  return i == 8 ? 0 : U->secret;
}