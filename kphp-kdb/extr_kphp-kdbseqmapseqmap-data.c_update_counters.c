#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct item {int size; int delta; int plus_unsure; int minus_unsure; TYPE_2__* right; TYPE_1__* left; } ;
struct TYPE_4__ {scalar_t__ plus_unsure; scalar_t__ minus_unsure; scalar_t__ delta; scalar_t__ size; } ;
struct TYPE_3__ {scalar_t__ plus_unsure; scalar_t__ minus_unsure; scalar_t__ delta; scalar_t__ size; } ;

/* Variables and functions */
 int NODE_TYPE_MINUS ; 
 int NODE_TYPE_PLUS ; 
 int NODE_TYPE_S (struct item*) ; 
 int NODE_TYPE_SURE ; 
 int NODE_TYPE_T (struct item*) ; 
 int NODE_TYPE_UNSURE ; 
 int NODE_TYPE_ZERO ; 
 int /*<<< orphan*/  assert (int) ; 

void update_counters (struct item *T) {
  if (!T) { return; }
  T->size = 1;
  int x = NODE_TYPE_T (T);
  int u = NODE_TYPE_S (T);
  if (x == NODE_TYPE_PLUS) {
    T->delta = 1;
    if (u == NODE_TYPE_UNSURE) {
      T->plus_unsure = 1;
    }
    T->minus_unsure = 0;
  } else if (x == NODE_TYPE_MINUS) {
    T->delta = -1;
    if (u == NODE_TYPE_UNSURE) {
      T->minus_unsure = 1;
    }
    T->plus_unsure = 0;
  } else {
    assert (x == NODE_TYPE_ZERO);
    T->delta = 0;
    assert (u == NODE_TYPE_SURE);
    T->minus_unsure = 0;
    T->plus_unsure = 0;
  }
  if (T->left) {
    T->size += T->left->size;
    T->delta += T->left->delta;
    T->minus_unsure += T->left->minus_unsure;
    T->plus_unsure += T->left->plus_unsure;
  }
  if (T->right) {
    T->size += T->right->size;
    T->delta += T->right->delta;
    T->minus_unsure += T->right->minus_unsure;
    T->plus_unsure += T->right->plus_unsure;
  }
}