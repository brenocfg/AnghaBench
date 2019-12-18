#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct warc_s {scalar_t__ cntoff; scalar_t__ cntlen; unsigned int unconsumed; } ;
struct archive_read {TYPE_1__* format; } ;
typedef  size_t ssize_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {struct warc_s* data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 char* __archive_read_ahead (struct archive_read*,unsigned int,size_t*) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,int) ; 

__attribute__((used)) static int
_warc_read(struct archive_read *a, const void **buf, size_t *bsz, int64_t *off)
{
	struct warc_s *w = a->format->data;
	const char *rab;
	ssize_t nrd;

	if (w->cntoff >= w->cntlen) {
	eof:
		/* it's our lucky day, no work, we can leave early */
		*buf = NULL;
		*bsz = 0U;
		*off = w->cntoff + 4U/*for \r\n\r\n separator*/;
		w->unconsumed = 0U;
		return (ARCHIVE_EOF);
	}

	if (w->unconsumed) {
		__archive_read_consume(a, w->unconsumed);
		w->unconsumed = 0U;
	}

	rab = __archive_read_ahead(a, 1U, &nrd);
	if (nrd < 0) {
		*bsz = 0U;
		/* big catastrophe */
		return (int)nrd;
	} else if (nrd == 0) {
		goto eof;
	} else if ((size_t)nrd > w->cntlen - w->cntoff) {
		/* clamp to content-length */
		nrd = w->cntlen - w->cntoff;
	}
	*off = w->cntoff;
	*bsz = nrd;
	*buf = rab;

	w->cntoff += nrd;
	w->unconsumed = (size_t)nrd;
	return (ARCHIVE_OK);
}