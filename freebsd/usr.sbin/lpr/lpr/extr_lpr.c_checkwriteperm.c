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
struct stat {int st_mode; scalar_t__ st_uid; } ;

/* Variables and functions */
 int S_ISVTX ; 
 int /*<<< orphan*/  W_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 scalar_t__ userid ; 

__attribute__((used)) static int
checkwriteperm(const char *file, const char *directory)
{
	struct	stat	stats;
	if (access(directory, W_OK) == 0) {
		stat(directory, &stats);
		if (stats.st_mode & S_ISVTX) {
			stat(file, &stats);
			if(stats.st_uid == userid) {
				return(0);
			}
		} else return(0);
	}
	return(-1);
}