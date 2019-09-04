#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tar_config ; 
 int nr_tar_filters ; 
 int /*<<< orphan*/  register_archiver (TYPE_1__*) ; 
 TYPE_1__ tar_archiver ; 
 int /*<<< orphan*/  tar_filter_config (char*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__** tar_filters ; 

void init_tar_archiver(void)
{
	int i;
	register_archiver(&tar_archiver);

	tar_filter_config("tar.tgz.command", "gzip -cn", NULL);
	tar_filter_config("tar.tgz.remote", "true", NULL);
	tar_filter_config("tar.tar.gz.command", "gzip -cn", NULL);
	tar_filter_config("tar.tar.gz.remote", "true", NULL);
	git_config(git_tar_config, NULL);
	for (i = 0; i < nr_tar_filters; i++) {
		/* omit any filters that never had a command configured */
		if (tar_filters[i]->data)
			register_archiver(tar_filters[i]);
	}
}