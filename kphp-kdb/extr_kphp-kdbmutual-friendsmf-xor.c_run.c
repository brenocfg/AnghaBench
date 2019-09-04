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
 scalar_t__ A1 ; 
 scalar_t__ A2 ; 
 scalar_t__ B1 ; 
 scalar_t__ B1a ; 
 scalar_t__ B1b ; 
 scalar_t__ B2 ; 
 scalar_t__ B2a ; 
 scalar_t__ B2b ; 
 int my_read1 () ; 
 int my_read2 () ; 
 int /*<<< orphan*/  my_write (scalar_t__*,int) ; 

void run (void) {
  int f1 = 1, f2 = 1;
  while (f1 || f2) {
    if (f1 && f2 && A1 == A2 && B1 == B2) {
      f1 = my_read1();
      f2 = my_read2();
    } else if (!f2 || (f1 && (A1 < A2 || (A1 == A2 && (B1a < B2a || (B1a == B2a && B1b < B2b)))))) {
      my_write (&A1, sizeof (int));
      my_write (&B1, sizeof (int));
      f1 = my_read1();
    } else {
      my_write (&A2, sizeof (int));
      my_write (&B2, sizeof (int));
      f2 = my_read2();
    }
  }
}