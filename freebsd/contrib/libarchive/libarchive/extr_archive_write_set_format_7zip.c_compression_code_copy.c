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
struct la_zstream {size_t avail_out; size_t avail_in; size_t next_out; size_t next_in; size_t total_in; size_t total_out; } ;
struct archive {int dummy; } ;
typedef  enum la_zaction { ____Placeholder_la_zaction } la_zaction ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_Z_FINISH ; 
 int /*<<< orphan*/  memcpy (size_t,size_t,size_t) ; 

__attribute__((used)) static int
compression_code_copy(struct archive *a,
    struct la_zstream *lastrm, enum la_zaction action)
{
	size_t bytes;

	(void)a; /* UNUSED */
	if (lastrm->avail_out > lastrm->avail_in)
		bytes = lastrm->avail_in;
	else
		bytes = lastrm->avail_out;
	if (bytes) {
		memcpy(lastrm->next_out, lastrm->next_in, bytes);
		lastrm->next_in += bytes;
		lastrm->avail_in -= bytes;
		lastrm->total_in += bytes;
		lastrm->next_out += bytes;
		lastrm->avail_out -= bytes;
		lastrm->total_out += bytes;
	}
	if (action == ARCHIVE_Z_FINISH && lastrm->avail_in == 0)
		return (ARCHIVE_EOF);
	return (ARCHIVE_OK);
}