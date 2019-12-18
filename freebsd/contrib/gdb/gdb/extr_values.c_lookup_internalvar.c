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
struct internalvar {struct internalvar* next; int /*<<< orphan*/  value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  allocate_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  builtin_type_void ; 
 int /*<<< orphan*/  concat (char*,int /*<<< orphan*/ *) ; 
 struct internalvar* internalvars ; 
 int /*<<< orphan*/  release_value (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ xmalloc (int) ; 

struct internalvar *
lookup_internalvar (char *name)
{
  struct internalvar *var;

  for (var = internalvars; var; var = var->next)
    if (strcmp (var->name, name) == 0)
      return var;

  var = (struct internalvar *) xmalloc (sizeof (struct internalvar));
  var->name = concat (name, NULL);
  var->value = allocate_value (builtin_type_void);
  release_value (var->value);
  var->next = internalvars;
  internalvars = var;
  return var;
}