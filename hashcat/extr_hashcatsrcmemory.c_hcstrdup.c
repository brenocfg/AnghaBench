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
 scalar_t__ hcmalloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t const) ; 
 size_t strlen (char const*) ; 

char *hcstrdup (const char *s)
{
  const size_t len = strlen (s);

  char *b = (char *) hcmalloc (len + 1);

  if (b == NULL) return (NULL);

  memcpy (b, s, len);

  b[len] = 0;

  return (b);
}