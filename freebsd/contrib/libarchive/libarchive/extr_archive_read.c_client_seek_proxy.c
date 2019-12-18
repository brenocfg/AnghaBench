#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct archive_read_filter {int /*<<< orphan*/  data; TYPE_2__* archive; } ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* seeker ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  archive; TYPE_1__ client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int /*<<< orphan*/  ARCHIVE_FAILED ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int64_t
client_seek_proxy(struct archive_read_filter *self, int64_t offset, int whence)
{
	/* DO NOT use the skipper here!  If we transparently handled
	 * forward seek here by using the skipper, that will break
	 * other libarchive code that assumes a successful forward
	 * seek means it can also seek backwards.
	 */
	if (self->archive->client.seeker == NULL) {
		archive_set_error(&self->archive->archive, ARCHIVE_ERRNO_MISC,
		    "Current client reader does not support seeking a device");
		return (ARCHIVE_FAILED);
	}
	return (self->archive->client.seeker)(&self->archive->archive,
	    self->data, offset, whence);
}