#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct user_groups* grp; } ;
typedef  TYPE_1__ user_t ;
struct user_groups {int cur_groups; int* G; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  del_user_group (TYPE_1__*,int) ; 

__attribute__((used)) static int del_groups (user_t *U, int List[], int len) {
  if (len < 0) {
    return -1;
  }
  if (!U || !len || !U->grp) {
    return 0;
  }

  struct user_groups *G = U->grp;
  int i, j = 0, k = 0;

  for (i = 1; i < len; i++) {
    assert (List[i-1] < List[i]);
  }


  for (i = 0; i < G->cur_groups; i++) {
    while (j < len && List[j] < G->G[i]) {
      j++;
    }
    if (j < len && List[j] == G->G[i]) {
      del_user_group (U, List[j++]);
    } else {
      G->G[k++] = G->G[i];
    }
  }

  i -= k;
  G->cur_groups = k;
  return i;
}