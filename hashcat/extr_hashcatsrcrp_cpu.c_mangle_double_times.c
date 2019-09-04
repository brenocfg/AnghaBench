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
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int mangle_double_times (char arr[RP_PASSWORD_SIZE], int arr_len, int times)
{
  if (((arr_len * times) + arr_len) >= RP_PASSWORD_SIZE) return (arr_len);

  int orig_len = arr_len;

  int i;

  for (i = 0; i < times; i++)
  {
    memcpy (&arr[arr_len], arr, orig_len);

    arr_len += orig_len;
  }

  return (arr_len);
}