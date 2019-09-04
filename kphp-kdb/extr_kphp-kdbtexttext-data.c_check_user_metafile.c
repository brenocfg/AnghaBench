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
struct TYPE_5__ {TYPE_1__* mf; } ;
typedef  TYPE_2__ user_t ;
struct TYPE_4__ {int len; scalar_t__ aio; } ;

/* Variables and functions */
 TYPE_2__* get_user (long long) ; 

int check_user_metafile (long long user_id, int *R) {
  user_t *U = get_user (user_id);

  if (!U || !U->mf || U->mf->aio) {
    return 0;
  }

  if (R) {
    R[0] = U->mf->len;
  }

  return 1;
}