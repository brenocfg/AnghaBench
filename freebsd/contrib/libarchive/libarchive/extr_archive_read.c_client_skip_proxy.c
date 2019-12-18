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
struct archive_read_filter {int position; int /*<<< orphan*/  data; TYPE_2__* archive; } ;
typedef  int int64_t ;
struct TYPE_3__ {int (* skipper ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;int (* seeker ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  archive; TYPE_1__ client; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  __archive_errx (int,char*) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t
client_skip_proxy(struct archive_read_filter *self, int64_t request)
{
	if (request < 0)
		__archive_errx(1, "Negative skip requested.");
	if (request == 0)
		return 0;

	if (self->archive->client.skipper != NULL) {
		/* Seek requests over 1GiB are broken down into
		 * multiple seeks.  This avoids overflows when the
		 * requests get passed through 32-bit arguments. */
		int64_t skip_limit = (int64_t)1 << 30;
		int64_t total = 0;
		for (;;) {
			int64_t get, ask = request;
			if (ask > skip_limit)
				ask = skip_limit;
			get = (self->archive->client.skipper)
				(&self->archive->archive, self->data, ask);
			total += get;
			if (get == 0 || get == request)
				return (total);
			if (get > request)
				return ARCHIVE_FATAL;
			request -= get;
		}
	} else if (self->archive->client.seeker != NULL
		&& request > 64 * 1024) {
		/* If the client provided a seeker but not a skipper,
		 * we can use the seeker to skip forward.
		 *
		 * Note: This isn't always a good idea.  The client
		 * skipper is allowed to skip by less than requested
		 * if it needs to maintain block alignment.  The
		 * seeker is not allowed to play such games, so using
		 * the seeker here may be a performance loss compared
		 * to just reading and discarding.  That's why we
		 * only do this for skips of over 64k.
		 */
		int64_t before = self->position;
		int64_t after = (self->archive->client.seeker)
		    (&self->archive->archive, self->data, request, SEEK_CUR);
		if (after != before + request)
			return ARCHIVE_FATAL;
		return after - before;
	}
	return 0;
}