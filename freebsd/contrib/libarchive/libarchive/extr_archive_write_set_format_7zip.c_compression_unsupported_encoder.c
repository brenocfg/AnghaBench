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
struct la_zstream {int /*<<< orphan*/ * real_stream; scalar_t__ valid; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FAILED ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static int
compression_unsupported_encoder(struct archive *a,
    struct la_zstream *lastrm, const char *name)
{

	archive_set_error(a, ARCHIVE_ERRNO_MISC,
	    "%s compression not supported on this platform", name);
	lastrm->valid = 0;
	lastrm->real_stream = NULL;
	return (ARCHIVE_FAILED);
}