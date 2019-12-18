#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mi_cmd {int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  rehash; int /*<<< orphan*/  hit; int /*<<< orphan*/  miss; } ;

/* Variables and functions */
 unsigned int MI_TABLE_SIZE ; 
 struct mi_cmd** mi_table ; 
 TYPE_1__ stats ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mi_cmd **
lookup_table (const char *command)
{
  const char *chp;
  unsigned int index = 0;
  /* compute our hash */
  for (chp = command; *chp; chp++)
    {
      /* some what arbitrary */
      index = ((index << 6) + (unsigned int) *chp) % MI_TABLE_SIZE;
    }
  /* look it up */
  while (1)
    {
      struct mi_cmd **entry = &mi_table[index];
      if ((*entry) == 0)
	{
	  /* not found, return pointer to next free. */
	  stats.miss++;
	  return entry;
	}
      if (strcmp (command, (*entry)->name) == 0)
	{
	  stats.hit++;
	  return entry;		/* found */
	}
      index = (index + 1) % MI_TABLE_SIZE;
      stats.rehash++;
    }
}