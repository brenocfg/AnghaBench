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
struct TYPE_5__ {scalar_t__ x; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ privacy_t ;
typedef  scalar_t__ privacy_key_t ;

/* Variables and functions */

__attribute__((used)) static void privacy_split (privacy_t **L, privacy_t **R, privacy_t *T, privacy_key_t x) {
  if (!T) { *L = *R = 0; return; }
  if (x < T->x) {
    *R = T;
    privacy_split (L, &T->left, T->left, x);
  } else {
    *L = T;
    privacy_split (&T->right, R, T->right, x);
  }
}