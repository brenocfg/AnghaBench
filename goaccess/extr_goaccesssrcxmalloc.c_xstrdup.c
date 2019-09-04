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
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 
 char* xmalloc (size_t) ; 

char *
xstrdup (const char *s)
{
  char *ptr;
  size_t len;

  len = strlen (s) + 1;
  ptr = xmalloc (len);

  strncpy (ptr, s, len);
  return (ptr);
}