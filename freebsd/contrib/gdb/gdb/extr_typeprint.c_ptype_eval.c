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
struct type {int dummy; } ;
struct expression {TYPE_1__* elts; } ;
struct TYPE_2__ {scalar_t__ opcode; struct type* type; } ;

/* Variables and functions */
 scalar_t__ OP_TYPE ; 

__attribute__((used)) static struct type *
ptype_eval (struct expression *exp)
{
  if (exp->elts[0].opcode == OP_TYPE)
    {
      return (exp->elts[1].type);
    }
  else
    {
      return (NULL);
    }
}