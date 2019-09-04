#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dirent {char* d_name; } ;
struct TYPE_2__ {int hexsz; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gc_auto_threshold ; 
 int /*<<< orphan*/  git_path (char*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 unsigned int const strspn (char*,char*) ; 
 TYPE_1__* the_hash_algo ; 

__attribute__((used)) static int too_many_loose_objects(void)
{
	/*
	 * Quickly check if a "gc" is needed, by estimating how
	 * many loose objects there are.  Because SHA-1 is evenly
	 * distributed, we can check only one and get a reasonable
	 * estimate.
	 */
	DIR *dir;
	struct dirent *ent;
	int auto_threshold;
	int num_loose = 0;
	int needed = 0;
	const unsigned hexsz_loose = the_hash_algo->hexsz - 2;

	dir = opendir(git_path("objects/17"));
	if (!dir)
		return 0;

	auto_threshold = DIV_ROUND_UP(gc_auto_threshold, 256);
	while ((ent = readdir(dir)) != NULL) {
		if (strspn(ent->d_name, "0123456789abcdef") != hexsz_loose ||
		    ent->d_name[hexsz_loose] != '\0')
			continue;
		if (++num_loose > auto_threshold) {
			needed = 1;
			break;
		}
	}
	closedir(dir);
	return needed;
}