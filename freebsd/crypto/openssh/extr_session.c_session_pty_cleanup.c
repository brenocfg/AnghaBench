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
typedef  int /*<<< orphan*/  Session ;

/* Variables and functions */
 int /*<<< orphan*/  PRIVSEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_pty_cleanup2 (int /*<<< orphan*/ *) ; 

void
session_pty_cleanup(Session *s)
{
	PRIVSEP(session_pty_cleanup2(s));
}