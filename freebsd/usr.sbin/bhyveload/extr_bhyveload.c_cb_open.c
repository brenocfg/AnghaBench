#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ fd; int /*<<< orphan*/  dir; } ;
struct TYPE_4__ {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  st_size; } ;
struct cb_file {int cf_isdir; TYPE_1__ cf_u; TYPE_2__ cf_stat; int /*<<< orphan*/  cf_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int PATH_MAX ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct cb_file*) ; 
 int /*<<< orphan*/  host_base ; 
 struct cb_file* malloc (int) ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opendir (char*) ; 
 scalar_t__ stat (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
cb_open(void *arg, const char *filename, void **hp)
{
	struct cb_file *cf;
	char path[PATH_MAX];

	if (!host_base)
		return (ENOENT);

	strlcpy(path, host_base, PATH_MAX);
	if (path[strlen(path) - 1] == '/')
		path[strlen(path) - 1] = 0;
	strlcat(path, filename, PATH_MAX);
	cf = malloc(sizeof(struct cb_file));
	if (stat(path, &cf->cf_stat) < 0) {
		free(cf);
		return (errno);
	}

	cf->cf_size = cf->cf_stat.st_size;
	if (S_ISDIR(cf->cf_stat.st_mode)) {
		cf->cf_isdir = 1;
		cf->cf_u.dir = opendir(path);
		if (!cf->cf_u.dir)
			goto out;
		*hp = cf;
		return (0);
	}
	if (S_ISREG(cf->cf_stat.st_mode)) {
		cf->cf_isdir = 0;
		cf->cf_u.fd = open(path, O_RDONLY);
		if (cf->cf_u.fd < 0)
			goto out;
		*hp = cf;
		return (0);
	}

out:
	free(cf);
	return (EINVAL);
}