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
typedef  int /*<<< orphan*/  uiAreaHandler ;
typedef  int /*<<< orphan*/  uiArea ;

/* Variables and functions */
 int /*<<< orphan*/  label ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  uiCheckboxSetChecked (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void handlerMouseCrossed(uiAreaHandler *ah, uiArea *a, int left)
{
printf("%d %d\n", left, !left);
	uiCheckboxSetChecked(label, !left);
}