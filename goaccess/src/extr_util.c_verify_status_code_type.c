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
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 char const* _ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** code_type ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char const) ; 

const char *
verify_status_code_type (const char *str)
{
  size_t i;
  for (i = 0; i < ARRAY_SIZE (code_type); i++)
    if (strchr (code_type[i][0], str[0]) != NULL)
      return _(code_type[i][1]);

  return "Unknown";
}