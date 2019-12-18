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

/* Variables and functions */
 scalar_t__ GT ; 
 int Gc ; 
 int* I ; 
 int* L ; 
 int MAX_GID ; 
 int MAX_GROUPS ; 
 int /*<<< orphan*/ * S ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

void process_names_row (void) {
  int x = I[0], len = L[1];

  if (x <= 0 || x >= MAX_GID) {
    return;
  }

  assert (Gc < MAX_GROUPS - len - 16);

  ((int *) GT)[x] = Gc;
  *((int *) (GT + Gc)) = len;
  Gc += 4;
  memcpy (GT + Gc, S[1], len+1);
  Gc = (Gc + len + 4) & -4;

  assert (Gc <= MAX_GROUPS);

  adj_rec++;

}