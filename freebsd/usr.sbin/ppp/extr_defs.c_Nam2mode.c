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
struct TYPE_2__ {int mode; char* name; } ;

/* Variables and functions */
 TYPE_1__* modes ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncasecmp (char const*,char*,int) ; 

int
Nam2mode(const char *name)
{
  int m, got, len;

  len = strlen(name);
  got = -1;
  for (m = 0; modes[m].mode; m++)
    if (!strncasecmp(name, modes[m].name, len)) {
      if (modes[m].name[len] == '\0')
	return modes[m].mode;
      if (got != -1)
        return 0;
      got = m;
    }

  return got == -1 ? 0 : modes[got].mode;
}