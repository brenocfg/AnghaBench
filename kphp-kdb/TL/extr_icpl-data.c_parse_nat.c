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
typedef  int icpl_nat_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (char const) ; 

__attribute__((used)) static icpl_nat_t parse_nat (const char *input, int l) {
  icpl_nat_t u = 0;
  int i;
  for (i = 0; i < l; i++) {
    assert (isdigit (input[i]));
    u = u * 10 + (input[i] - 48);
  }
  return u;
}