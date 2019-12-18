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
struct ppmd_stream {struct ppmd_stream* buff; int /*<<< orphan*/  ppmd7_context; } ;
struct la_zstream {scalar_t__ valid; int /*<<< orphan*/ * real_stream; } ;
struct archive {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* Ppmd7_Free ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 TYPE_1__ __archive_ppmd7_functions ; 
 int /*<<< orphan*/  free (struct ppmd_stream*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
compression_end_ppmd(struct archive *a, struct la_zstream *lastrm)
{
	struct ppmd_stream *strm;

	(void)a; /* UNUSED */

	strm = (struct ppmd_stream *)lastrm->real_stream;
	__archive_ppmd7_functions.Ppmd7_Free(&strm->ppmd7_context);
	free(strm->buff);
	free(strm);
	lastrm->real_stream = NULL;
	lastrm->valid = 0;
	return (ARCHIVE_OK);
}