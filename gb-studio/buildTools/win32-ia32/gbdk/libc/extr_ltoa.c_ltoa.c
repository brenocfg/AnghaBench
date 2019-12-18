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
typedef  int UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  reverse (char*) ; 

char *ltoa(long n, char *s)
{
  UINT8 i, sign;

  if(n < 0) {
    sign = 1;
    n = -n;
  } else
    sign = 0;
  i = 0;
  do {
    s[i++] = n % 10 + '0';
  } while((n = n/10) > 0);
  if(sign)
    s[i++] = '-';
  s[i] = 0;
  reverse(s);
  return s;
}