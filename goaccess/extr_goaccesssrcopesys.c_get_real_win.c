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
 char* alloc_string (char*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static char *
get_real_win (const char *win)
{
  if (strstr (win, "10.0"))
    return alloc_string ("Windows 10");
  else if (strstr (win, "6.3"))
    return alloc_string ("Windows 8.1");
  else if (strstr (win, "6.3; ARM"))
    return alloc_string ("Windows RT");
  else if (strstr (win, "6.2; ARM"))
    return alloc_string ("Windows RT");
  else if (strstr (win, "6.2"))
    return alloc_string ("Windows 8");
  else if (strstr (win, "6.1"))
    return alloc_string ("Windows 7");
  else if (strstr (win, "6.0"))
    return alloc_string ("Windows Vista");
  else if (strstr (win, "5.2"))
    return alloc_string ("Windows XP x64");
  else if (strstr (win, "5.1"))
    return alloc_string ("Windows XP");
  else if (strstr (win, "5.0"))
    return alloc_string ("Windows 2000");
  return NULL;
}