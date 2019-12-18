#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* cat_ver; int /*<<< orphan*/  fr_tree; int /*<<< orphan*/  pr_tree; } ;
typedef  TYPE_1__ user_t ;
struct TYPE_8__ {int cat; } ;
typedef  TYPE_2__ tree_t ;
struct TYPE_9__ {int* List; int y; } ;
typedef  TYPE_3__ privacy_t ;
typedef  int /*<<< orphan*/  privacy_key_t ;

/* Variables and functions */
 int CAT_FR_ALL ; 
 int CAT_FR_FR ; 
 int MAX_PRIVACY_LEN ; 
 int PL_M_CAT ; 
 int PL_M_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* get_user (int) ; 
 int is_friends_friend (int,int) ; 
 TYPE_3__* privacy_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* tree_lookup (int /*<<< orphan*/ ,int) ; 

int check_privacy (int checker_id, int user_id, privacy_key_t privacy_key) {
  if (checker_id < 0 || user_id <= 0 || !privacy_key) {
    return -1;
  }
  if (!checker_id) {
    checker_id = -1;
  }
  if (checker_id == user_id) {
    return 3;
  }

  user_t *U = get_user (user_id);
  if (!U) {
    return -1;
  }

  privacy_t *P = privacy_lookup (U->pr_tree, privacy_key);
  if (!P) {
    return -1;
  }

  int *A = P->List, len = (P->y & 0xff);
  if (len == 255) {
    len = *A++;
    assert (len >= 255 && len <= MAX_PRIVACY_LEN);
  }
  assert (A[len] == -1);

  int x, y, z = 0, t = 3, m = -1;

  while (t) {
    x = *A++;
    if (x == -1) {
      t = 0;
      break;
    }
    if (!x) {
      continue;
    }
    y = x & PL_M_MASK;
    if (x & PL_M_CAT) {
      if (y == CAT_FR_ALL) {
        break;
      }
      if (y == CAT_FR_FR) {
        if (m == -1) {
          tree_t *N = tree_lookup (U->fr_tree, checker_id);
          m = (N ? N->cat : 0);
        }
        int w = (m > 0 ? 1 : is_friends_friend (user_id, checker_id));
        if (w > 0) {
          break;
        } else if (w < 0) {
          if (x >= 0) {
            z |= t & 1;
          }
          t &= 2;
        }
        continue;
      }
      if (y != U->cat_ver[y & 0x1f]) {
        A[-1] = 0;
        continue;
      }
      if (m == -1) {
        tree_t *N = tree_lookup (U->fr_tree, checker_id);
        m = (N ? N->cat : 0);
      }
      if ((m >> (y & 0x1f)) & 1) {
        break;
      }
    } else if (y == checker_id) {
      break;
    }
  }

  if (x >= 0) {
    z |= t;
  }
  return z;
}