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
struct TYPE_2__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ cmpsuff (char const*,int /*<<< orphan*/ *) ; 
 TYPE_1__* names ; 

__attribute__((used)) static int get_array_index(const char *name)
{
  int i;

  for (i = 0; names[i].name != NULL; i++) 
  {
    if (cmpsuff(name, names[i].name) == 0)
      return i;
  }    
  return -1;
  
}