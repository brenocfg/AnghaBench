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
struct TYPE_4__ {struct user_langs* langs; } ;
typedef  TYPE_1__ user_t ;
struct user_langs {int cur_langs; int tot_langs; int /*<<< orphan*/ * L; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_user_lang (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct user_langs*,int) ; 

__attribute__((used)) static void user_clear_langs (user_t *U) {
  struct user_langs *L = U->langs;

  if (L) {
    int i;
    for (i = 0; i < L->cur_langs; i++) { 
      del_user_lang (U, L->L[i]);
    }
    zfree (L, sizeof (struct user_langs) + L->tot_langs*2);
  }

  U->langs = 0;
}