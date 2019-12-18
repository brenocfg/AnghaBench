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
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,int*,int) ; 

__attribute__((used)) static int
read_int(const char *path)
{
	int input;

	input = open(path, O_RDONLY);
	if (input == -1)
		return -1;
	else {
		int value;
		ATF_REQUIRE_EQ(read(input, &value, sizeof(value)), sizeof(value));
		close(input);
		return value;
	}
}