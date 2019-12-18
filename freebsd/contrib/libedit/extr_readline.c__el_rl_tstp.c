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
typedef  int /*<<< orphan*/  EditLine ;

/* Variables and functions */
 unsigned char CC_NORM ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char
_el_rl_tstp(EditLine *el __attribute__((__unused__)), int ch __attribute__((__unused__)))
{
	(void)kill(0, SIGTSTP);
	return CC_NORM;
}