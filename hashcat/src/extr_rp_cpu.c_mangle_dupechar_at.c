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
 int mangle_insert (char*,int,int,char) ; 

__attribute__((used)) static int mangle_dupechar_at (char arr[RP_PASSWORD_SIZE], int arr_len, int upos, int ulen)
{
  if ( arr_len         ==  0) return (arr_len);
  if ((arr_len + ulen) >= RP_PASSWORD_SIZE) return (arr_len);

  char c = arr[upos];

  int i;

  for (i = 0; i < ulen; i++)
  {
    arr_len = mangle_insert (arr, arr_len, upos, c);
  }

  return (arr_len);
}