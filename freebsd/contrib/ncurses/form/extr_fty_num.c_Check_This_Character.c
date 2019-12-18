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
struct TYPE_2__ {struct lconv* L; } ;
typedef  TYPE_1__ thisARG ;
struct lconv {int dummy; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ isDecimalPoint (int) ; 
 scalar_t__ isDigit (int) ; 

__attribute__((used)) static bool
Check_This_Character(int c, const void *argp)
{
  const thisARG *argn = (const thisARG *)argp;
  struct lconv *L = argn->L;

  return ((isDigit(c) ||
	   c == '+' ||
	   c == '-' ||
	   isDecimalPoint(c))
	  ? TRUE
	  : FALSE);
}