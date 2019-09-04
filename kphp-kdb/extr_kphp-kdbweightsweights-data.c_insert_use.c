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
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* prev; } ;
typedef  TYPE_1__ weights_vector_t ;

/* Variables and functions */

__attribute__((used)) static void insert_use (weights_vector_t *u, weights_vector_t *V, weights_vector_t *v) {
  u->next = V; V->prev = u;
  v->prev = V; V->next = v;
}