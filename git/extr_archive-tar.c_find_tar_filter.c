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
struct archiver {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int nr_tar_filters ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char const*,int) ; 
 struct archiver** tar_filters ; 

__attribute__((used)) static struct archiver *find_tar_filter(const char *name, int len)
{
	int i;
	for (i = 0; i < nr_tar_filters; i++) {
		struct archiver *ar = tar_filters[i];
		if (!strncmp(ar->name, name, len) && !ar->name[len])
			return ar;
	}
	return NULL;
}