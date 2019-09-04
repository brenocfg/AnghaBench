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
typedef  int UInt64 ;

/* Variables and functions */

__attribute__((used)) static void UInt64ToStr(UInt64 value, char *s, int numDigits)
{
  char temp[32];
  int pos = 0;
  do
  {
    temp[pos++] = (char)('0' + (unsigned)(value % 10));
    value /= 10;
  }
  while (value != 0);

  for (numDigits -= pos; numDigits > 0; numDigits--)
    *s++ = ' ';

  do
    *s++ = temp[--pos];
  while (pos);
  *s = '\0';
}