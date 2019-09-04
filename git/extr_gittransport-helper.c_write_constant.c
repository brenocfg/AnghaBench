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
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ write_in_full (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_constant(int fd, const char *str)
{
	if (debug)
		fprintf(stderr, "Debug: Remote helper: -> %s", str);
	if (write_in_full(fd, str, strlen(str)) < 0)
		die_errno(_("full write to remote helper failed"));
}