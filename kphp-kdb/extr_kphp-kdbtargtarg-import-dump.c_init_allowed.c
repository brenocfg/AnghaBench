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
 int* allowed ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void init_allowed (void) {
  int i;
  memset (allowed, 0, 256);
  for (i = '0'; i <= '9'; i++) { allowed[i] = 4; }
  for (i = 'A'; i <= 'Z'; i++) { allowed[i] = 2; }
  for (i = 'a'; i <= 'z'; i++) { allowed[i] = 1; }
  allowed['-'] = 8;
  allowed[','] = 8;
}