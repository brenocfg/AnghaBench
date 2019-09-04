#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tree {int nc; int size; struct tree** c; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct tree**) ; 
 int /*<<< orphan*/  memcpy (void**,struct tree**,int) ; 
 int /*<<< orphan*/  zfree (struct tree**,int) ; 
 void** zmalloc (int) ; 

void tree_add_child (struct tree *P, struct tree *C) {
  if (P->nc == P->size) {
    void **t = zmalloc (sizeof (void *) * (++P->size));
    memcpy (t, P->c, sizeof (void *) * (P->size - 1));
    if (P->c) {
      zfree (P->c, sizeof (void *) * (P->size - 1));
    }
    P->c = (void *)t;
    assert (P->c);
  }
  P->c[P->nc ++] = C;
}