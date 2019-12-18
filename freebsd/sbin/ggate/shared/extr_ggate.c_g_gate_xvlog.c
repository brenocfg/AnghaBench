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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gate_vlog (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void
g_gate_xvlog(const char *message, va_list ap)
{

	g_gate_vlog(LOG_ERR, message, ap);
	g_gate_vlog(LOG_ERR, "Exiting.", ap);
	exit(EXIT_FAILURE);
}