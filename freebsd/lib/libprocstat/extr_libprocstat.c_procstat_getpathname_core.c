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
struct procstat_core {int dummy; } ;
struct kinfo_file {scalar_t__ kf_fd; int /*<<< orphan*/  kf_path; } ;

/* Variables and functions */
 scalar_t__ KF_FD_TYPE_TEXT ; 
 int /*<<< orphan*/  free (struct kinfo_file*) ; 
 struct kinfo_file* kinfo_getfile_core (struct procstat_core*,int*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
procstat_getpathname_core(struct procstat_core *core, char *pathname,
    size_t maxlen)
{
	struct kinfo_file *files;
	int cnt, i, result;

	files = kinfo_getfile_core(core, &cnt);
	if (files == NULL)
		return (-1);
	result = -1;
	for (i = 0; i < cnt; i++) {
		if (files[i].kf_fd != KF_FD_TYPE_TEXT)
			continue;
		strncpy(pathname, files[i].kf_path, maxlen);
		result = 0;
		break;
	}
	free(files);
	return (result);
}