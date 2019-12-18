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

__attribute__((used)) static int mangle_insert (char arr[RP_PASSWORD_SIZE], int arr_len, int upos, char c)
{
  if (upos > arr_len) return (arr_len);

  if ((arr_len + 1) >= RP_PASSWORD_SIZE) return (arr_len);

  int arr_pos;

  for (arr_pos = arr_len - 1; arr_pos > upos - 1; arr_pos--)
  {
    arr[arr_pos + 1] = arr[arr_pos];
  }

  arr[upos] = c;

  return (arr_len + 1);
}