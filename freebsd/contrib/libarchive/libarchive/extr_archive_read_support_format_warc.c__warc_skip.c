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
struct warc_s {unsigned int cntlen; unsigned int cntoff; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {struct warc_s* data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,unsigned int) ; 

__attribute__((used)) static int
_warc_skip(struct archive_read *a)
{
	struct warc_s *w = a->format->data;

	__archive_read_consume(a, w->cntlen + 4U/*\r\n\r\n separator*/);
	w->cntlen = 0U;
	w->cntoff = 0U;
	return (ARCHIVE_OK);
}