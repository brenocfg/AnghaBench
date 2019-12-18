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
 scalar_t__ EACCES ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static int
is_file(const char* fname)
{
	struct stat buf;
	if(stat(fname, &buf) < 0) {
		if(errno==EACCES) {
			printf("warning: no search permission for one of the directories in path: %s\n", fname);
			return 1;
		}
		perror(fname);
		return 0;
	}
	if(S_ISDIR(buf.st_mode)) {
		printf("%s is not a file\n", fname);
		return 0;
	}
	return 1;
}