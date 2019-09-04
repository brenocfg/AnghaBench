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
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/ * log_invalid ; 

void
invalid_log_open (const char *path)
{
  if (path != NULL) {
    log_invalid = fopen (path, "w");
    if (log_invalid == NULL)
      return;
  }
}