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
struct TYPE_5__ {scalar_t__ gl_pathc; int /*<<< orphan*/ * gl_pathv; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  gl ;

/* Variables and functions */
 int GLOB_BRACE ; 
 int GLOB_NOCHECK ; 
 int GLOB_QUOTE ; 
 int GLOB_TILDE ; 
 int /*<<< orphan*/  doglob ; 
 scalar_t__ glob (char*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
globulize(char **cpp)
{
	glob_t gl;
	int flags;

	if (!doglob)
		return (1);

	flags = GLOB_BRACE|GLOB_NOCHECK|GLOB_QUOTE|GLOB_TILDE;
	memset(&gl, 0, sizeof(gl));
	if (glob(*cpp, flags, NULL, &gl) ||
	    gl.gl_pathc == 0) {
		warnx("%s: not found", *cpp);
		globfree(&gl);
		return (0);
	}
	*cpp = strdup(gl.gl_pathv[0]);	/* XXX - wasted memory */
	globfree(&gl);
	return (1);
}