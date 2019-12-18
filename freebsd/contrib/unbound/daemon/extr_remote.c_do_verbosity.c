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
 int atoi (char*) ; 
 int /*<<< orphan*/  send_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int verbosity ; 

__attribute__((used)) static void
do_verbosity(RES* ssl, char* str)
{
	int val = atoi(str);
	if(val == 0 && strcmp(str, "0") != 0) {
		ssl_printf(ssl, "error in verbosity number syntax: %s\n", str);
		return;
	}
	verbosity = val;
	send_ok(ssl);
}