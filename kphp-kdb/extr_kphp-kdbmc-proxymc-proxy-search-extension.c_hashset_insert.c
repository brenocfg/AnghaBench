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
 long long* H ; 
 unsigned int HSIZE ; 

__attribute__((used)) static int hashset_insert (long long id) {
  /* empty hash always stored */
  if (!id) { return 1; }
  int h1, h2;
  long long D;
  h1 = ((unsigned int) id) % HSIZE;
  h2 = 1 + ((unsigned int) (id >> 32)) % (HSIZE - 1);
  while ((D = H[h1]) != 0) {
    if (D == id) {
      return 0;
    }
    h1 += h2;
    if (h1 >= HSIZE) { h1 -= HSIZE; }
  }
  H[h1] = id;
  return 1;
}