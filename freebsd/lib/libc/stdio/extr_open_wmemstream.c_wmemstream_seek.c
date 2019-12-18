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
struct wmemstream {scalar_t__ offset; scalar_t__ len; int /*<<< orphan*/  mbstate; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ fpos_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 scalar_t__ FPOS_MAX ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct wmemstream*,scalar_t__,...) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  wmemstream_update (struct wmemstream*) ; 

__attribute__((used)) static fpos_t
wmemstream_seek(void *cookie, fpos_t pos, int whence)
{
	struct wmemstream *ms;
	fpos_t old;

	ms = cookie;
	old = ms->offset;
	switch (whence) {
	case SEEK_SET:
		/* _fseeko() checks for negative offsets. */
		assert(pos >= 0);
		ms->offset = pos;
		break;
	case SEEK_CUR:
		/* This is only called by _ftello(). */
		assert(pos == 0);
		break;
	case SEEK_END:
		if (pos < 0) {
			if (pos + ms->len < 0) {
#ifdef DEBUG
				fprintf(stderr,
				    "WMS: bad SEEK_END: pos %jd, len %zd\n",
				    (intmax_t)pos, ms->len);
#endif
				errno = EINVAL;
				return (-1);
			}
		} else {
			if (FPOS_MAX - ms->len < pos) {
#ifdef DEBUG
				fprintf(stderr,
				    "WMS: bad SEEK_END: pos %jd, len %zd\n",
				    (intmax_t)pos, ms->len);
#endif
				errno = EOVERFLOW;
				return (-1);
			}
		}
		ms->offset = ms->len + pos;
		break;
	}
	/* Reset the multibyte state if a seek changes the position. */
	if (ms->offset != old)
		memset(&ms->mbstate, 0, sizeof(ms->mbstate));
	wmemstream_update(ms);
#ifdef DEBUG
	fprintf(stderr, "WMS: seek(%p, %jd, %d) %jd -> %jd\n", ms,
	    (intmax_t)pos, whence, (intmax_t)old, (intmax_t)ms->offset);
#endif
	return (ms->offset);
}