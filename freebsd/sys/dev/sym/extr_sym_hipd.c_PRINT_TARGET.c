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
typedef  int /*<<< orphan*/  hcb_p ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 char* sym_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void PRINT_TARGET (hcb_p np, int target)
{
	printf ("%s:%d:", sym_name(np), target);
}