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
 int /*<<< orphan*/  gets (char*) ; 
 scalar_t__ isspace (char) ; 

__attribute__((used)) static UINT8 scan_skip(char *s, UINT8 i)
{
oncemore:
  while(isspace(s[i]))
    i++;
  if(s[i] == 0) {
    gets(s);
    i = 0;
    goto oncemore;
  }
  return i;
}