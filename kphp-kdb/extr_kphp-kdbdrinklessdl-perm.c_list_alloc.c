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
struct TYPE_4__ {int a; int b; struct TYPE_4__* r; struct TYPE_4__* l; } ;
typedef  TYPE_1__ perm_list ;

/* Variables and functions */
 TYPE_1__* dl_malloc (int) ; 

perm_list* list_alloc (int a, int b) {
  perm_list *v = dl_malloc (sizeof (perm_list));
  v->l = v->r = v;
  v->a = a;
  v->b = b;
  return v;
}