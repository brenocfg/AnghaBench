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
typedef  int /*<<< orphan*/  pathtmp ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ IS_DOT (char*) ; 
 scalar_t__ IS_DOTDOT (char*) ; 
 int PATH_MAX ; 
 int errno ; 
 int /*<<< orphan*/  getc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  mtree_current ; 
 int /*<<< orphan*/  mtree_error (char*) ; 
 int /*<<< orphan*/  mtree_root ; 
 int read_mtree_spec1 (int /*<<< orphan*/ *,int,char*) ; 
 int read_word (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  skip_to (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strlen (char*) ; 
 int strnunvis (char*,int,char*) ; 

__attribute__((used)) static int
read_mtree_spec(FILE *fp)
{
	char pathspec[PATH_MAX], pathtmp[4*PATH_MAX + 1];
	char *cp;
	int error;

	error = read_word(fp, pathtmp, sizeof(pathtmp));
	if (error)
		goto out;
	if (strnunvis(pathspec, PATH_MAX, pathtmp) == -1) {
		error = errno;
		goto out;
	}
	error = 0;

	cp = strchr(pathspec, '/');
	if (cp != NULL) {
		/* Absolute pathname */
		mtree_current = mtree_root;

		do {
			*cp++ = '\0';

			/* Disallow '..' as a component. */
			if (IS_DOTDOT(pathspec)) {
				mtree_error("absolute path cannot contain "
				    ".. component");
				goto out;
			}

			/* Ignore multiple adjacent slashes and '.'. */
			if (pathspec[0] != '\0' && !IS_DOT(pathspec))
				error = read_mtree_spec1(fp, false, pathspec);
			memmove(pathspec, cp, strlen(cp) + 1);
			cp = strchr(pathspec, '/');
		} while (!error && cp != NULL);

		/* Disallow '.' and '..' as the last component. */
		if (!error && (IS_DOT(pathspec) || IS_DOTDOT(pathspec))) {
			mtree_error("absolute path cannot contain . or .. "
			    "components");
			goto out;
		}
	}

	/* Ignore absolute specfications that end with a slash. */
	if (!error && pathspec[0] != '\0')
		error = read_mtree_spec1(fp, true, pathspec);

 out:
	skip_to(fp, "\n");
	(void)getc(fp);
	return (error);
}