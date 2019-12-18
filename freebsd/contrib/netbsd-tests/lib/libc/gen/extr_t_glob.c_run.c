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
struct TYPE_5__ {size_t gl_pathc; int /*<<< orphan*/ * gl_pathv; int /*<<< orphan*/  gl_lstat; int /*<<< orphan*/  gl_stat; int /*<<< orphan*/  gl_closedir; int /*<<< orphan*/  gl_readdir; int /*<<< orphan*/  gl_opendir; } ;
typedef  TYPE_1__ glob_t ;
typedef  int /*<<< orphan*/  gl ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_CHECK (int) ; 
 int /*<<< orphan*/  ATF_CHECK_STREQ (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int GLOB_ALTDIRFUNC ; 
 int /*<<< orphan*/  RZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_closedir ; 
 int /*<<< orphan*/  gl_lstat ; 
 int /*<<< orphan*/  gl_opendir ; 
 int /*<<< orphan*/  gl_readdir ; 
 int /*<<< orphan*/  gl_stat ; 
 int /*<<< orphan*/  glob (char const*,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  globfree (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
run(const char *p, int flags, const char **res, size_t len)
{
	glob_t gl;
	size_t i;

	memset(&gl, 0, sizeof(gl));
	gl.gl_opendir = gl_opendir;
	gl.gl_readdir = gl_readdir;
	gl.gl_closedir = gl_closedir;
	gl.gl_stat = gl_stat;
	gl.gl_lstat = gl_lstat;

	RZ(glob(p, GLOB_ALTDIRFUNC | flags, NULL, &gl));

	for (i = 0; i < gl.gl_pathc; i++)
		DPRINTF(("%s\n", gl.gl_pathv[i]));

	ATF_CHECK(len == gl.gl_pathc);
	for (i = 0; i < gl.gl_pathc; i++)
		ATF_CHECK_STREQ(gl.gl_pathv[i], res[i]);

	globfree(&gl);
}