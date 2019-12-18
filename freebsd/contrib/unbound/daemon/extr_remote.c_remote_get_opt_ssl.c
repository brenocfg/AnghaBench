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
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,char*) ; 

void remote_get_opt_ssl(char* line, void* arg)
{
	RES* ssl = (RES*)arg;
	(void)ssl_printf(ssl, "%s\n", line);
}