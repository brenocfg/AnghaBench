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
struct serial_ops {int /*<<< orphan*/  name; struct serial_ops* next; } ;

/* Variables and functions */
 struct serial_ops* serial_ops_list ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct serial_ops *
serial_interface_lookup (char *name)
{
  struct serial_ops *ops;

  for (ops = serial_ops_list; ops; ops = ops->next)
    if (strcmp (name, ops->name) == 0)
      return ops;

  return NULL;
}