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
struct tui_translate {scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ strcmp (scalar_t__,char const*) ; 

__attribute__((used)) static struct tui_translate *
translate (const char *name, struct tui_translate *table)
{
  while (table->name)
    {
      if (name && strcmp (table->name, name) == 0)
        return table;
      table++;
    }

  /* Not found, return default entry.  */
  table++;
  return table;
}