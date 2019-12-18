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
 int /*<<< orphan*/  TerminalAutoFlush () ; 
 int /*<<< orphan*/  autoflush ; 
 int /*<<< orphan*/  exit (int) ; 
 int ring_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ttyibuf ; 
 int /*<<< orphan*/  ttyiring ; 
 int /*<<< orphan*/  ttyobuf ; 
 int /*<<< orphan*/  ttyoring ; 

void
init_terminal(void)
{
    if (ring_init(&ttyoring, ttyobuf, sizeof ttyobuf) != 1) {
	exit(1);
    }
    if (ring_init(&ttyiring, ttyibuf, sizeof ttyibuf) != 1) {
	exit(1);
    }
    autoflush = TerminalAutoFlush();
}