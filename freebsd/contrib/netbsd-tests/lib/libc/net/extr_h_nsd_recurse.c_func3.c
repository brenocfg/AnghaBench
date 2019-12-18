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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int NS_SUCCESS ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
func3(void *rv, void *cb_data, va_list ap)
{
	(void)printf("func3: enter\n");
	(void)printf("func3: exit\n");

	return NS_SUCCESS;
}