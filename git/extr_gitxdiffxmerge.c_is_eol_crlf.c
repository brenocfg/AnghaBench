#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nrec; TYPE_1__** recs; } ;
typedef  TYPE_2__ xdfile_t ;
struct TYPE_4__ {long size; char* ptr; } ;

/* Variables and functions */

__attribute__((used)) static int is_eol_crlf(xdfile_t *file, int i)
{
	long size;

	if (i < file->nrec - 1)
		/* All lines before the last *must* end in LF */
		return (size = file->recs[i]->size) > 1 &&
			file->recs[i]->ptr[size - 2] == '\r';
	if (!file->nrec)
		/* Cannot determine eol style from empty file */
		return -1;
	if ((size = file->recs[i]->size) &&
			file->recs[i]->ptr[size - 1] == '\n')
		/* Last line; ends in LF; Is it CR/LF? */
		return size > 1 &&
			file->recs[i]->ptr[size - 2] == '\r';
	if (!i)
		/* The only line has no eol */
		return -1;
	/* Determine eol from second-to-last line */
	return (size = file->recs[i - 1]->size) > 1 &&
		file->recs[i - 1]->ptr[size - 2] == '\r';
}