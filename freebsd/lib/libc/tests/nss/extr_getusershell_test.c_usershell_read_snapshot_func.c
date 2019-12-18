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
struct usershell {int /*<<< orphan*/ * path; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

__attribute__((used)) static int
usershell_read_snapshot_func(struct usershell *us, char *line)
{

	us->path = strdup(line);
	ATF_REQUIRE(us->path != NULL);

	return (0);
}