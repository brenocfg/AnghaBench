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
struct TYPE_2__ {int equal; int /*<<< orphan*/ * arch; int /*<<< orphan*/ * sec; int /*<<< orphan*/ * manpath; void* query; } ;
struct req {TYPE_1__ q; scalar_t__ isquery; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (unsigned char) ; 
 void* mandoc_strdup (char const*) ; 
 void* mandoc_strndup (char const*,int) ; 
 int /*<<< orphan*/  pg_error_badrequest (char*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ validate_arch (int /*<<< orphan*/ *) ; 
 scalar_t__ validate_manpath (struct req*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
parse_path_info(struct req *req, const char *path)
{
	const char	*name, *sec, *end;

	req->isquery = 0;
	req->q.equal = 1;
	req->q.manpath = NULL;
	req->q.arch = NULL;

	/* Mandatory manual page name. */
	if ((name = strrchr(path, '/')) == NULL)
		name = path;
	else
		name++;

	/* Optional trailing section. */
	sec = strrchr(name, '.');
	if (sec != NULL && isdigit((unsigned char)*++sec)) {
		req->q.query = mandoc_strndup(name, sec - name - 1);
		req->q.sec = mandoc_strdup(sec);
	} else {
		req->q.query = mandoc_strdup(name);
		req->q.sec = NULL;
	}

	/* Handle the case of name[.section] only. */
	if (name == path)
		return;

	/* Optional manpath. */
	end = strchr(path, '/');
	req->q.manpath = mandoc_strndup(path, end - path);
	if (validate_manpath(req, req->q.manpath)) {
		path = end + 1;
		if (name == path)
			return;
	} else {
		free(req->q.manpath);
		req->q.manpath = NULL;
	}

	/* Optional section. */
	if (strncmp(path, "man", 3) == 0 || strncmp(path, "cat", 3) == 0) {
		path += 3;
		end = strchr(path, '/');
		free(req->q.sec);
		req->q.sec = mandoc_strndup(path, end - path);
		path = end + 1;
		if (name == path)
			return;
	}

	/* Optional architecture. */
	end = strchr(path, '/');
	if (end + 1 != name) {
		pg_error_badrequest(
		    "You specified too many directory components.");
		exit(EXIT_FAILURE);
	}
	req->q.arch = mandoc_strndup(path, end - path);
	if (validate_arch(req->q.arch) == 0) {
		pg_error_badrequest(
		    "You specified an invalid directory component.");
		exit(EXIT_FAILURE);
	}
}