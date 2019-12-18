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
struct stat {int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int fstatat (int,char const*,struct stat*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static off_t
file_size(int savedirfd, const char *path)
{
	struct stat sb;

	/* Ignore all errors, this file may not exist. */
	if (fstatat(savedirfd, path, &sb, 0) == -1)
		return (0);
	return (sb.st_size);
}