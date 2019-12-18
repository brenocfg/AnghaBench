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
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

void
svn_wc__eol_value_from_string(const char **value, const char *eol)
{
  if (eol == NULL)
    *value = NULL;
  else if (! strcmp("\n", eol))
    *value = "LF";
  else if (! strcmp("\r", eol))
    *value = "CR";
  else if (! strcmp("\r\n", eol))
    *value = "CRLF";
  else
    *value = NULL;
}