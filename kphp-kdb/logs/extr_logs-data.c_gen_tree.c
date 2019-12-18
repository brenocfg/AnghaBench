#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ type; } ;
typedef  TYPE_1__ token ;
struct TYPE_11__ {TYPE_1__ tok; } ;
typedef  TYPE_2__ node ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL ; 
 scalar_t__ IS_OP (scalar_t__) ; 
 int /*<<< orphan*/  IS_PREFIX_UN (scalar_t__) ; 
 int /*<<< orphan*/  OK ; 
 TYPE_1__* dl_malloc (int) ; 
 TYPE_2__** dl_malloc0 (int) ; 
 scalar_t__ end_token ; 
 TYPE_2__* new_node () ; 
 scalar_t__ op_lb ; 
 size_t op_rb ; 
 int /*<<< orphan*/ * priority ; 
 int /*<<< orphan*/  upd (TYPE_2__**,TYPE_1__*,int*,int*,int /*<<< orphan*/ ) ; 

node *gen_tree (token *v) {
  if (v == NULL) {
    return NULL;
  }

  token *t = v;
  while (t->type != end_token) {
    t++;
  }
  int n = t - v, i;

  int tsize = n;

  node **s1 = dl_malloc0 (tsize * sizeof (node *));
  token *s2 = dl_malloc (tsize * sizeof (token));
  int s1n = 0, s2n = 0;

#define FAIL for (i = 0; i < s1n; i++) { \
               del_node (s1[i]);         \
             }                           \
             OK;                         \
             return NULL

#define OK dl_free (s1, tsize * sizeof (node *));    \
           dl_free (s2, tsize * sizeof (token))

  for (i = 0; i < n; i++) {
    if (IS_OP(v[i].type)) { // op
      if (v[i].type == op_lb) {
        s2[s2n++] = v[i];
      } else {
        if (!IS_PREFIX_UN(v[i].type) && !upd (s1, s2, &s1n, &s2n, priority[v[i].type])) {
          FAIL;
        }
        if (v[i].type == op_rb) {
          if (!s2n || s2[s2n - 1].type != op_lb) {
            FAIL;
          }
          s2n--;
        } else {
          s2[s2n++] = v[i];
        }
      }
    } else {
      s1[s1n] = new_node();
      s1[s1n++]->tok = v[i];
    }
  }
  if (!upd (s1, s2, &s1n, &s2n, priority[op_rb]) || s1n != 1 || s2n) {
    FAIL;
  }
  node *res = s1[0];
  OK;

#undef FAIL
#undef OK
  return res;
}