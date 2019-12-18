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

/* Variables and functions */
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct value* value_primitive_field (struct value*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct value *
value_field (struct value *arg1, int fieldno)
{
  return value_primitive_field (arg1, 0, fieldno, VALUE_TYPE (arg1));
}