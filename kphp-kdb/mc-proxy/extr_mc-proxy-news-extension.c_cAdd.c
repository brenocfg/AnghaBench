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
struct collection {int num; long long* A; } ;

/* Variables and functions */
 int MAX_C_NUM ; 

__attribute__((used)) static void cAdd (struct collection *C, int item, int owner) {
  long long x = (unsigned) item + (((long long) owner) << 32);
  int i;
  for (i = 0; i < C->num; i++) {
    if (C->A[i] == x) {
      return;
    }
  }
  if (C->num < MAX_C_NUM) {
    C->A[C->num++] = x;
  }
}