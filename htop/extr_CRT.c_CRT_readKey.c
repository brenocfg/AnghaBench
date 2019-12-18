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
 int /*<<< orphan*/  CRT_delay ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  cbreak () ; 
 int getch () ; 
 int /*<<< orphan*/  halfdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nocbreak () ; 
 int /*<<< orphan*/  nodelay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdscr ; 

int CRT_readKey() {
   nocbreak();
   cbreak();
   nodelay(stdscr, FALSE);
   int ret = getch();
   halfdelay(CRT_delay);
   return ret;
}