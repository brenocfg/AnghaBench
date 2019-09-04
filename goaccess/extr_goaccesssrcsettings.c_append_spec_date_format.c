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
 scalar_t__ snprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*) ; 
 char* xmalloc (scalar_t__) ; 

__attribute__((used)) static char *
append_spec_date_format (const char *date_format, const char *spec_format)
{
  char *s = xmalloc (snprintf (NULL, 0, "%s%s", date_format, spec_format) + 1);
  sprintf (s, "%s%s", date_format, spec_format);

  return s;
}