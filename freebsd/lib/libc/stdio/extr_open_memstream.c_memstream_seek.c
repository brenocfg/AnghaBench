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
struct memstream {int offset; int len; } ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int fpos_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 int FPOS_MAX ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct memstream*,int,...) ; 
 int /*<<< orphan*/  memstream_update (struct memstream*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static fpos_t
memstream_seek(void *cookie, fpos_t pos, int whence)
{
	struct memstream *ms;
#ifdef DEBUG
	fpos_t old;
#endif

	ms = cookie;
#ifdef DEBUG
	old = ms->offset;
#endif
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
				    "MS: bad SEEK_END: pos %jd, len %zd\n",
				    (intmax_t)pos, ms->len);
#endif
				errno = EINVAL;
				return (-1);
			}
		} else {
			if (FPOS_MAX - ms->len < pos) {
#ifdef DEBUG
				fprintf(stderr,
				    "MS: bad SEEK_END: pos %jd, len %zd\n",
				    (intmax_t)pos, ms->len);
#endif
				errno = EOVERFLOW;
				return (-1);
			}
		}
		ms->offset = ms->len + pos;
		break;
	}
	memstream_update(ms);
#ifdef DEBUG
	fprintf(stderr, "MS: seek(%p, %jd, %d) %jd -> %jd\n", ms, (intmax_t)pos,
	    whence, (intmax_t)old, (intmax_t)ms->offset);
#endif
	return (ms->offset);
}