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
struct memstream {scalar_t__ len; char** bufp; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ fpos_t ;

/* Variables and functions */
 scalar_t__ SSIZE_MAX ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct memstream*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 char* realloc (char*,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
memstream_grow(struct memstream *ms, fpos_t newoff)
{
	char *buf;
	ssize_t newsize;

	if (newoff < 0 || newoff >= SSIZE_MAX)
		newsize = SSIZE_MAX - 1;
	else
		newsize = newoff;
	if (newsize > ms->len) {
		buf = realloc(*ms->bufp, newsize + 1);
		if (buf != NULL) {
#ifdef DEBUG
			fprintf(stderr, "MS: %p growing from %zd to %zd\n",
			    ms, ms->len, newsize);
#endif
			memset(buf + ms->len + 1, 0, newsize - ms->len);
			*ms->bufp = buf;
			ms->len = newsize;
			return (1);
		}
		return (0);
	}
	return (1);
}