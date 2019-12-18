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
 char const CHAR_NULL ; 
 char* error_texts ; 

__attribute__((used)) static const char *
find_error_text(int n)
{
const char *s = error_texts;
for (; n > 0; n--)
  {
  while (*s++ != CHAR_NULL) {};
  if (*s == CHAR_NULL) return "Error text not found (please report)";
  }
return s;
}