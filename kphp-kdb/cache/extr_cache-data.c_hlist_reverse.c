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
struct cache_uri {struct cache_uri* hnext; } ;

/* Variables and functions */

__attribute__((used)) static struct cache_uri *hlist_reverse (struct cache_uri *L) {
  struct cache_uri *U, *V, *A = NULL;
  for (U = L; U != NULL; U = V) {
    V = U->hnext;
    U->hnext = A;
    A = U;
  }
  return A;
}