#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int user_id; int cat_mask; int* cat_ver; } ;
typedef  TYPE_1__ user_t ;

/* Variables and functions */
 TYPE_1__** User ; 
 int conv_uid (int) ; 
 int max_uid ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tot_users ; 
 TYPE_1__* zmalloc (int) ; 

__attribute__((used)) static user_t *get_user_f (int user_id) {
  int i = conv_uid (user_id);
  user_t *U;
  if (i < 0) { return 0; }
  U = User[i];
  if (U) { return U; }
  U = zmalloc (sizeof (user_t));
  memset (U, 0, sizeof(user_t));
  U->user_id = i;
  U->cat_mask = 1;
  User[i] = U;
  if (i > max_uid) { max_uid = i; }
  tot_users++;

  for (i = 0; i < 31; i++) {
    U->cat_ver[i] = i;
  }
 
  return U;
}