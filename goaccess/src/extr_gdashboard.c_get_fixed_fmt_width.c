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
 scalar_t__ snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static char *
get_fixed_fmt_width (int w, char type)
{
  char *fmt = xmalloc (snprintf (NULL, 0, "%%%d%c", w, type) + 1);
  sprintf (fmt, "%%%d%c", w, type);

  return fmt;
}