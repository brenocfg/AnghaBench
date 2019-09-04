#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x1; int x2; struct TYPE_5__* left; struct TYPE_5__* middle; struct TYPE_5__* right; } ;
typedef  TYPE_1__ tree23_t ;

/* Variables and functions */
 int /*<<< orphan*/  free_leaf (TYPE_1__*) ; 
 int /*<<< orphan*/  free_node (TYPE_1__*) ; 

__attribute__((used)) static void tree23_delete (tree23_t **T, int x) {
  int *P = 0, *PP = 0;
  tree23_t *st[100];
  int sp = 0;
  tree23_t *cur = *T, *up, *succ;


  while (!(cur->x1 & 1)) {
    st[sp++] = cur;
    if (x > cur->x2) cur = cur->right;
    else
    if (x < cur->x1) cur = cur->left;
    else
    if (x == cur->x1) {
      P = &cur->x1;
      if (cur->x2 & 1) PP = &cur->x2;
      x += 2;
      --sp;
      break;
    }
    else
    if (x < (cur->x2 & -2)) cur = cur->middle;
    else {
      P = &cur->x2;
      x += 2;
      --sp;
      break;
    }
  }
  while (!(cur->x1 & 1)) {
    st[sp++] = cur;
    if (x < cur->x1) cur = cur->left;
    else
    if (x > cur->x2) cur = cur->right;
    else
    cur = cur->middle;
  }
  if (P) {
    *P = cur->x1 & -2;
    if (PP) *PP = cur->x1;
  } else 
  if (x == cur->x2) {
    cur->x2 = cur->x1;
    return;
  }
  if (!(cur->x2&1)) {
    cur->x1 = cur->x2 |= 1;
    return;
  }
  //oh, no...
  //printf ("%d\n", sp);
  if (sp == 0) {
    free_leaf (cur);
    *T = 0;
    return;
  }
  up = st[--sp];
  if (up->right == cur) {
    if (up->x2 & 1) {
      if (up->left->x2 & 1) {
        up->left->x2 = up->x1;
        free_leaf (cur);
        succ = up->left;
        //continue to the top
      } else {
        cur->x1 = cur->x2 = up->x2;
        up->x1 = up->left->x2;
        up->left->x2 = up->left->x1;
        up->x2 = up->x1 | 1;
        return;
      }
    } else {
      if (up->middle->x2 & 1) {
        if (up->left->x2 & 1) {
          up->middle->x2 = up->x2;
          free_leaf (cur);
          up->x2 = up->x1 | 1;
          up->right = up->middle;
          return;
        } else {
          cur->x1 = cur->x2 = up->x2 | 1;
          up->x2 = up->middle->x1 & -2;
          up->middle->x1 = up->middle->x2 = up->x1 | 1;
          up->x1 = up->left->x2;
          up->left->x2 = up->left->x1;
          return;
        }
      } else {
        cur->x1 = cur->x2 = up->x2 | 1;
        up->x2 = up->middle->x2;
        up->middle->x2 = up->middle->x1;
        return;
      }
    }
  } else 
  if (up->left == cur) {
    if (up->x2 & 1) {
      if (up->right->x2 & 1) {
        up->right->x1 = up->x1 | 1;
        up->right->x2 &= -2;
        free_leaf (cur);
        succ = up->right;
        //continue to the top
      } else {
        cur->x1 = cur->x2 = up->x2;
        up->x1 = (up->x2 = up->right->x1) & -2;
        up->right->x1 = up->right->x2 |= 1;
        return;
      }
    } else {
      if (up->middle->x2 & 1) {
        if (up->right->x2 & 1) {
          up->middle->x1 = up->x1 | 1;
          up->middle->x2 &= -2;
          up->left = up->middle;
          up->x1 = up->x2;
          up->x2 |= 1;
          free_leaf (cur);
          return;
        } else {
          cur->x1 = cur->x2 = up->x1 | 1;
          up->x1 = up->middle->x2 & -2;
          up->middle->x1 = up->middle->x2 = up->x2 | 1;
          up->x2 = up->right->x1 & -2;
          up->right->x1 = up->right->x2 |= 1;
          return;
        }
      } else {
        cur->x1 = cur->x2 = up->x1 | 1;
        up->x1 = up->middle->x1 & -2;
        up->middle->x1 = up->middle->x2 |= 1;
        return;
      }
    }
  } else {
    if (up->left->x2 & 1) {
      if (up->right->x2 & 1) {
        up->right->x2 &= -2;
        up->right->x1 = up->x2 | 1;
        up->x2 = up->x1 | 1;
        free_leaf (cur);
        return;
      } else {
        cur->x1 = cur->x2 = up->x2 | 1;
        up->x2 = up->right->x1 & -2;
        up->right->x1 = up->right->x2 |= 1;
        return;
      }
    } else {
      cur->x1 = cur->x2 = up->x1 | 1;
      up->x1 = up->left->x2;
      up->left->x2 = up->left->x1;
      return;
    }
  }

  while (sp) {
    cur = up;
    up = st[--sp];
    if (up->right == cur) {
      if (up->x2 & 1) {
        if (up->left->x2 & 1) {
          up->left->x2 = up->x1;
          up->left->middle = up->left->right;
          up->left->right = succ;
          free_node (cur);
          succ = up->left;
        } else {
          cur->x2 = up->x2;
          cur->x1 = cur->x2 & -2;
          cur->right = succ;
          cur->left = up->left->right;
          up->x1 = up->left->x2;
          up->left->x2 = up->left->x1 | 1;
          up->x2 = up->x1 | 1;
          up->left->right=up->left->middle;
          return;
        }
      } else {
        if (up->middle->x2 & 1) {
          if (up->left->x2 & 1) {
            up->middle->x2 = up->x2;
            free_node (cur);
            up->x2 = up->x1 | 1;
            up->middle->middle = up->middle->right;
            up->middle->right = succ;
            up->right = up->middle;
            return;
          } else {
            cur->x1 = up->x2;
            cur->x2 = cur->x1 | 1;
            cur->right = succ;
            cur->left = up->middle->right;
            up->x2 = up->middle->x1;
            up->middle->x1 = up->x1;
            up->middle->x2 = up->x1 | 1;
            up->middle->right = up->middle->left;
            up->middle->left = up->left->right;
            up->x1 = up->left->x2;
            up->left->x2 = up->left->x1 | 1;
            up->left->right = up->left->middle;
            return;
          }
        } else {
          cur->x1 = up->x2;
          cur->x2 = cur->x1 | 1;
          cur->right = succ;
          cur->left = up->middle->right;
          up->x2 = up->middle->x2;
          up->middle->x2 = up->middle->x1 | 1;
          up->middle->right = up->middle->middle;
          return;
        }
      }
    } else
    if (up->left == cur) {
      if (up->x2 & 1) {
        if (up->right->x2 & 1) {
          up->right->x1 = up->x1;
          up->right->x2 &= -2;
          free_node (cur);
          up->right->middle = up->right->left;
          up->right->left = succ;
          succ = up->right;
          //continue to the top
        } else {
          cur ->x2 = (cur->x1 = up->x1) | 1;
          cur->left = succ;
          cur->right = up->right->left;
          up->right->left = up->right->middle;
          up->x2 = (up->x1 = up->right->x1) | 1;
          up->right->x2 = (up->right->x1 = up->right->x2) | 1;
          return;
        }
      } else {
        if (up->middle->x2 & 1) {
          if (up->right->x2 & 1) {
            up->middle->x1 = up->x1;
            up->middle->x2 &= -2;
            up->middle->middle = up->middle->left;
            up->middle->left = succ;
            up->left = up->middle;
            up->x1 = up->x2;
            up->x2 |= 1;
            free_node (cur);
            return;
          } else {
            cur->x2 = (cur->x1 = up->x1) | 1;
            cur->left = succ;
            cur->right = up->middle->left;
            up->middle->left = up->middle->right;
            up->middle->right = up->right->left;
            up->right->left = up->right->middle;
            up->x1 = up->middle->x2 & -2;
            up->middle->x2 = (up->middle->x1 = up->x2) | 1;
            up->x2 = up->right->x1;
            up->right->x1 = up->right->x2;
            up->right->x2 |= 1;
            return;
          }
        } else {
          cur->left = succ;
          cur->right = up->middle->left;
          up->middle->left = up->middle->middle;
          cur->x2 = (cur->x1 = up->x1) | 1;
          up->x1 = up->middle->x1;
          up->middle->x1 = up->middle->x2;
          up->middle->x2 |= 1;
          return;
        }
      }
    } else {
      if (up->left->x2 & 1) {
        if (up->right->x2 & 1) {
          up->right->middle = up->right->left;
          up->right->left = succ;
          up->right->x2 &= -2;
          up->right->x1 = up->x2;
          up->x2 = up->x1 | 1;
          free_node (cur);
          return;
        } else {
          cur->left = succ;
          cur->right = up->right->left;
          up->right->left = up->right->middle;
          cur->x2 = (cur->x1 = up->x2) | 1;
          up->x2 = up->right->x1;
          up->right->x1 = up->right->x2;
          up->right->x2 |= 1;
          return;
        }
      } else {
        cur->right = succ;
        cur->left = up->left->right;
        up->left->right = up->left->middle;
        cur->x2 = (cur->x1 = up->x1) | 1;
        up->x1 = up->left->x2;
        up->left->x2 = up->left->x1 | 1;
        return;
      }
    }
  }

  free_node (up);
  *T = succ;
}