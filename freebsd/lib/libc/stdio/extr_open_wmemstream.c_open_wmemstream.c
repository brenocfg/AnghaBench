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
struct wmemstream {size_t* sizep; int /*<<< orphan*/  mbstate; scalar_t__ offset; scalar_t__ len; struct wmemstream** bufp; } ;
typedef  struct wmemstream wchar_t ;
typedef  int /*<<< orphan*/  mbstate_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 struct wmemstream* calloc (int,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct wmemstream*) ; 
 int /*<<< orphan*/ * funopen (struct wmemstream*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwide (int /*<<< orphan*/ *,int) ; 
 struct wmemstream* malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wmemstream_close ; 
 int /*<<< orphan*/  wmemstream_seek ; 
 int /*<<< orphan*/  wmemstream_update (struct wmemstream*) ; 
 int /*<<< orphan*/  wmemstream_write ; 

FILE *
open_wmemstream(wchar_t **bufp, size_t *sizep)
{
	struct wmemstream *ms;
	int save_errno;
	FILE *fp;

	if (bufp == NULL || sizep == NULL) {
		errno = EINVAL;
		return (NULL);
	}
	*bufp = calloc(1, sizeof(wchar_t));
	if (*bufp == NULL)
		return (NULL);
	ms = malloc(sizeof(*ms));
	if (ms == NULL) {
		save_errno = errno;
		free(*bufp);
		*bufp = NULL;
		errno = save_errno;
		return (NULL);
	}
	ms->bufp = bufp;
	ms->sizep = sizep;
	ms->len = 0;
	ms->offset = 0;
	memset(&ms->mbstate, 0, sizeof(mbstate_t));
	wmemstream_update(ms);
	fp = funopen(ms, NULL, wmemstream_write, wmemstream_seek,
	    wmemstream_close);
	if (fp == NULL) {
		save_errno = errno;
		free(ms);
		free(*bufp);
		*bufp = NULL;
		errno = save_errno;
		return (NULL);
	}
	fwide(fp, 1);
	return (fp);
}