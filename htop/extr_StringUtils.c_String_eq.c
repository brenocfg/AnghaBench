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
 scalar_t__ strcmp (char const*,char const*) ; 

inline int String_eq(const char* s1, const char* s2) {
   if (s1 == NULL || s2 == NULL) {
      if (s1 == NULL && s2 == NULL)
         return 1;
      else
         return 0;
   }
   return (strcmp(s1, s2) == 0);
}