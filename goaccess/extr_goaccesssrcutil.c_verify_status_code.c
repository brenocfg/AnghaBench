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
 int /*<<< orphan*/ ** codes ; 
 int /*<<< orphan*/ * strstr (char*,int /*<<< orphan*/ ) ; 

const char *
verify_status_code (char *str)
{
  size_t i;
  for (i = 0; i < ARRAY_SIZE (codes); i++)
    if (strstr (str, codes[i][0]) != NULL)
      return _(codes[i][1]);

  return "Unknown";
}