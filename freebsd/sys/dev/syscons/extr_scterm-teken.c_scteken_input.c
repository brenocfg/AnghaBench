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
struct tty {int dummy; } ;
typedef  int /*<<< orphan*/  scr_stat ;

/* Variables and functions */
 int FALSE ; 

__attribute__((used)) static int
scteken_input(scr_stat *scp, int c, struct tty *tp)
{

	return FALSE;
}