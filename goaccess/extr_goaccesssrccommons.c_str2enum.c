#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int idx; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ GEnum ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

int
str2enum (const GEnum map[], int len, const char *str)
{
  int i;

  for (i = 0; i < len; ++i) {
    if (!strcmp (str, map[i].str))
      return map[i].idx;
  }

  return -1;
}