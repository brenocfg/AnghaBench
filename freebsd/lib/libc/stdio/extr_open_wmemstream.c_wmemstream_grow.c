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
typedef  int /*<<< orphan*/  wchar_t ;
struct wmemstream {int len; int /*<<< orphan*/ ** bufp; } ;
typedef  int ssize_t ;
typedef  int fpos_t ;

/* Variables and functions */
 int SSIZE_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct wmemstream*,int,int) ; 
 int /*<<< orphan*/ * reallocarray (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wmemset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
wmemstream_grow(struct wmemstream *ms, fpos_t newoff)
{
	wchar_t *buf;
	ssize_t newsize;

	if (newoff < 0 || newoff >= SSIZE_MAX / sizeof(wchar_t))
		newsize = SSIZE_MAX / sizeof(wchar_t) - 1;
	else
		newsize = newoff;
	if (newsize > ms->len) {
		buf = reallocarray(*ms->bufp, newsize + 1, sizeof(wchar_t));
		if (buf != NULL) {
#ifdef DEBUG
			fprintf(stderr, "WMS: %p growing from %zd to %zd\n",
			    ms, ms->len, newsize);
#endif
			wmemset(buf + ms->len + 1, 0, newsize - ms->len);
			*ms->bufp = buf;
			ms->len = newsize;
			return (1);
		}
		return (0);
	}
	return (1);
}