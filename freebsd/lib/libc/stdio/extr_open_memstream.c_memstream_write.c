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
struct memstream {int offset; int len; int* bufp; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,struct memstream*,int,int) ; 
 int /*<<< orphan*/  memcpy (int,char const*,int) ; 
 int /*<<< orphan*/  memstream_grow (struct memstream*,int) ; 
 int /*<<< orphan*/  memstream_update (struct memstream*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
memstream_write(void *cookie, const char *buf, int len)
{
	struct memstream *ms;
	ssize_t tocopy;

	ms = cookie;
	if (!memstream_grow(ms, ms->offset + len))
		return (-1);
	tocopy = ms->len - ms->offset;
	if (len < tocopy)
		tocopy = len;
	memcpy(*ms->bufp + ms->offset, buf, tocopy);
	ms->offset += tocopy;
	memstream_update(ms);
#ifdef DEBUG
	fprintf(stderr, "MS: write(%p, %d) = %zd\n", ms, len, tocopy);
#endif
	return (tocopy);
}