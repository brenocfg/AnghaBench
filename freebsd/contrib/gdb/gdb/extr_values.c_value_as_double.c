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
typedef  int /*<<< orphan*/  DOUBLEST ;

/* Variables and functions */
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  unpack_double (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

DOUBLEST
value_as_double (struct value *val)
{
  DOUBLEST foo;
  int inv;

  foo = unpack_double (VALUE_TYPE (val), VALUE_CONTENTS (val), &inv);
  if (inv)
    error ("Invalid floating value found in program.");
  return foo;
}