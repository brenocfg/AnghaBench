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
struct internalvar {struct value* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_LENGTH (int /*<<< orphan*/ ) ; 
 char* VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_field (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  value_as_long (struct value*) ; 

void
set_internalvar_component (struct internalvar *var, int offset, int bitpos,
			   int bitsize, struct value *newval)
{
  char *addr = VALUE_CONTENTS (var->value) + offset;

  if (bitsize)
    modify_field (addr, value_as_long (newval),
		  bitpos, bitsize);
  else
    memcpy (addr, VALUE_CONTENTS (newval), TYPE_LENGTH (VALUE_TYPE (newval)));
}