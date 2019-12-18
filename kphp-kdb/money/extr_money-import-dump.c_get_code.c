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
typedef  int /*<<< orphan*/  money_auth_code_t ;

/* Variables and functions */
 int* L ; 
 char** S ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strtoull (char*,char**,int) ; 

money_auth_code_t get_code (int x) {
  char *ptr;
  money_auth_code_t res = strtoull (S[x], &ptr, 16);
  assert (!L[x] || (L[x] == 16 && ptr == S[x] + 16));
  return res;
}