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
struct user_groups {int cur_groups; int tot_groups; int /*<<< orphan*/ * G; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_user_group (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct user_groups*,int) ; 

__attribute__((used)) static void user_clear_groups (user_t *U) {
  struct user_groups *G = U->grp;

  if (G) {
    int i;
    for (i = 0; i < G->cur_groups; i++) { 
      del_user_group (U, G->G[i]);
    }
    zfree (G, sizeof (struct user_groups) + G->tot_groups*4);
  }

  U->grp = 0;
}