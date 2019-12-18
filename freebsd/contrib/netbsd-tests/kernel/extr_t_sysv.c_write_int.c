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
typedef  int /*<<< orphan*/  value ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,char const*) ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  write (int,int const*,int) ; 

__attribute__((used)) static void
write_int(const char *path, const int value)
{
	int output;

	output = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	ATF_REQUIRE_MSG(output != -1, "Failed to create %s", path);
	write(output, &value, sizeof(value));
	close(output);
}