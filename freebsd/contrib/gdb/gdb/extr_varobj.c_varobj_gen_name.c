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
 int /*<<< orphan*/  xasprintf (char**,char*,int) ; 

char *
varobj_gen_name (void)
{
  static int id = 0;
  char *obj_name;

  /* generate a name for this object */
  id++;
  xasprintf (&obj_name, "var%d", id);

  return obj_name;
}