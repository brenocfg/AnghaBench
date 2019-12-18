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
typedef  int /*<<< orphan*/  FunctionBar ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionBar_EnterEscEvents ; 
 int /*<<< orphan*/  FunctionBar_EnterEscKeys ; 
 int /*<<< orphan*/ * FunctionBar_new (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

FunctionBar* FunctionBar_newEnterEsc(const char* enter, const char* esc) {
   const char* functions[] = {enter, esc, NULL};
   return FunctionBar_new(functions, FunctionBar_EnterEscKeys, FunctionBar_EnterEscEvents);
}