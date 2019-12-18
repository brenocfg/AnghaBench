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
 int /*<<< orphan*/ * CRT_colors ; 
 size_t FUNCTION_BAR ; 
 int /*<<< orphan*/  FunctionBar_drawAttr (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 

void FunctionBar_draw(const FunctionBar* this, char* buffer) {
   FunctionBar_drawAttr(this, buffer, CRT_colors[FUNCTION_BAR]);
}