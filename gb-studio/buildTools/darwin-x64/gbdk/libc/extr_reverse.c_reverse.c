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
typedef  size_t UINT8 ;

/* Variables and functions */
 size_t strlen (char*) ; 

char *reverse(char *s)
{
  UINT8 i, j;
  char c;

  i = 0;
  j = strlen(s) - 1;
  while(i < j) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
    i++;
    j--;
  }
  return(s);
}