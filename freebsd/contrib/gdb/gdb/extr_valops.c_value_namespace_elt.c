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
struct value {int dummy; } ;
struct type {int dummy; } ;
typedef  enum noside { ____Placeholder_noside } noside ;

/* Variables and functions */
 char* TYPE_TAG_NAME (struct type const*) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 struct value* value_maybe_namespace_elt (struct type const*,char*,int) ; 

__attribute__((used)) static struct value *
value_namespace_elt (const struct type *curtype,
		     char *name,
		     enum noside noside)
{
  struct value *retval = value_maybe_namespace_elt (curtype, name,
						    noside);

  if (retval == NULL)
    error ("No symbol \"%s\" in namespace \"%s\".", name,
	   TYPE_TAG_NAME (curtype));

  return retval;
}