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
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ unlink (char const*) ; 

__attribute__((used)) static void
cleanup(const char *filename)
{

	if (unlink(filename))
		err(2, "could not delete: %s", filename);
	exit(2);
}