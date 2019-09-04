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
struct TYPE_4__ {scalar_t__ dtype; int /*<<< orphan*/ * v_cstring; int /*<<< orphan*/  v_string; } ;
struct TYPE_5__ {int vn; struct TYPE_5__** v; TYPE_1__ tok; } ;
typedef  TYPE_2__ node ;

/* Variables and functions */
 int /*<<< orphan*/  dl_strdup (int /*<<< orphan*/ *) ; 
 scalar_t__ v_cstring ; 
 scalar_t__ v_string ; 

int expression_prepare (node *v) {
  if (v == NULL) {
    return 1;
  }
  if (v->tok.dtype == v_cstring && v->tok.v_cstring != NULL) {
    v->tok.v_string = dl_strdup (v->tok.v_cstring);
    v->tok.dtype = v_string;
  }
  int i;
  for (i = 0; i < v->vn; i++) {
    if (!expression_prepare (v->v[i])) {
      return 0;
    }
  }
  return 1;
}