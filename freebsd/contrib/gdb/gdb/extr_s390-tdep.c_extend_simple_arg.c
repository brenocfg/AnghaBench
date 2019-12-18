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
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  TYPE_LENGTH (struct type*) ; 
 scalar_t__ TYPE_UNSIGNED (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  extract_signed_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_unsigned_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static LONGEST
extend_simple_arg (struct value *arg)
{
  struct type *type = VALUE_TYPE (arg);

  /* Even structs get passed in the least significant bits of the
     register / memory word.  It's not really right to extract them as
     an integer, but it does take care of the extension.  */
  if (TYPE_UNSIGNED (type))
    return extract_unsigned_integer (VALUE_CONTENTS (arg),
                                     TYPE_LENGTH (type));
  else
    return extract_signed_integer (VALUE_CONTENTS (arg),
                                   TYPE_LENGTH (type));
}