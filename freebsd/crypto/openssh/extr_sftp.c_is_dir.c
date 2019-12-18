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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int
is_dir(const char *path)
{
	struct stat sb;

	/* XXX: report errors? */
	if (stat(path, &sb) == -1)
		return(0);

	return(S_ISDIR(sb.st_mode));
}