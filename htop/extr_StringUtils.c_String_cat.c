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
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* xMalloc (int) ; 

char* String_cat(const char* s1, const char* s2) {
   int l1 = strlen(s1);
   int l2 = strlen(s2);
   char* out = xMalloc(l1 + l2 + 1);
   strncpy(out, s1, l1);
   strncpy(out+l1, s2, l2+1);
   return out;
}