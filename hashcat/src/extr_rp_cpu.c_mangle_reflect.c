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
 int RP_PASSWORD_SIZE ; 
 int /*<<< orphan*/  mangle_double (char*,int) ; 
 int /*<<< orphan*/  mangle_reverse (char*,int) ; 

__attribute__((used)) static int mangle_reflect (char arr[RP_PASSWORD_SIZE], int arr_len)
{
  if ((arr_len * 2) >= RP_PASSWORD_SIZE) return (arr_len);

  mangle_double (arr, arr_len);

  mangle_reverse (arr + arr_len, arr_len);

  return (arr_len * 2);
}