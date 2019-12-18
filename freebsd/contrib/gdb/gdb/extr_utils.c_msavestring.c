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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 scalar_t__ xmmalloc (void*,size_t) ; 

char *
msavestring (void *md, const char *ptr, size_t size)
{
  char *p = (char *) xmmalloc (md, size + 1);
  memcpy (p, ptr, size);
  p[size] = 0;
  return p;
}