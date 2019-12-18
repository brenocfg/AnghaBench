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

/* Variables and functions */
 int /*<<< orphan*/  T_OC_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digit ; 
 int /*<<< orphan*/  letter ; 
 int /*<<< orphan*/  lower ; 
 int /*<<< orphan*/  lws ; 
 int /*<<< orphan*/  p ; 
 int /*<<< orphan*/  pfcs ; 
 int /*<<< orphan*/  upper ; 
 int /*<<< orphan*/  ws ; 
 int /*<<< orphan*/  xdigit ; 

__attribute__((used)) static int
t_prepare(int argc, char *argv[])
{

	(void)argc;
	(void)argv;
	T_OC_ADD(digit);
	T_OC_ADD(xdigit);
	T_OC_ADD(upper);
	T_OC_ADD(lower);
	T_OC_ADD(letter);
	T_OC_ADD(lws);
	T_OC_ADD(ws);
	T_OC_ADD(p);
	T_OC_ADD(pfcs);
	return (0);
}