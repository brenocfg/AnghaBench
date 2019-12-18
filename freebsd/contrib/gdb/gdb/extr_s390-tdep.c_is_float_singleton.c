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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 struct type* TYPE_FIELD_TYPE (struct type*,int /*<<< orphan*/ ) ; 
 int TYPE_NFIELDS (struct type*) ; 

__attribute__((used)) static int
is_float_singleton (struct type *type)
{
  if (TYPE_CODE (type) == TYPE_CODE_STRUCT && TYPE_NFIELDS (type) == 1)
    {
      struct type *singleton_type = TYPE_FIELD_TYPE (type, 0);
      CHECK_TYPEDEF (singleton_type);

      return (TYPE_CODE (singleton_type) == TYPE_CODE_FLT
	      || is_float_singleton (singleton_type));
    }

  return 0;
}