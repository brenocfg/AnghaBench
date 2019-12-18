#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ gl_pathc; char const** gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  gl ;

/* Variables and functions */
 int GLOB_BRACE ; 
 int GLOB_NOCHECK ; 
 int GLOB_TILDE ; 
 int /*<<< orphan*/  doglob ; 
 char* ftp_strdup (char const*) ; 
 scalar_t__ glob (char const*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

char *
globulize(const char *pattern)
{
	glob_t gl;
	int flags;
	char *p;

	if (!doglob)
		return (ftp_strdup(pattern));

	flags = GLOB_BRACE|GLOB_NOCHECK|GLOB_TILDE;
	memset(&gl, 0, sizeof(gl));
	if (glob(pattern, flags, NULL, &gl) || gl.gl_pathc == 0) {
		warnx("Glob pattern `%s' not found", pattern);
		globfree(&gl);
		return (NULL);
	}
	p = ftp_strdup(gl.gl_pathv[0]);
	globfree(&gl);
	return (p);
}