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
 int PRIME ; 
 int* User ; 
 int* UserList ; 
 int /*<<< orphan*/  assert (int) ; 
 int tot_users ; 

int get_hash (int x) {
  assert (x > 0);
  int h1 = x % PRIME, h2 = x % (PRIME - 1) + 1;
  while (User[h1] && User[h1] != x) {
    h1 += h2;
    if (h1 >= PRIME) h1 -= PRIME;
  }
  if (!User[h1]) {
    User[h1] = x;
    assert (tot_users < PRIME / 2);
    UserList[tot_users++] = x;
  };
  
  return h1;
}