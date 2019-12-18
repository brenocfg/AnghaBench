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
struct aio_context {int ac_read_fd; int ac_write_fd; int ac_buflen; int /*<<< orphan*/  ac_seed; int /*<<< orphan*/  ac_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,...) ; 
 int BUFFER_MAX ; 
 int /*<<< orphan*/  aio_fill_buffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ aio_test_buffer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct aio_context*,int) ; 
 int /*<<< orphan*/  random () ; 
 int /*<<< orphan*/  srandomdev () ; 

__attribute__((used)) static void
aio_context_init(struct aio_context *ac, int read_fd,
    int write_fd, int buflen)
{

	ATF_REQUIRE_MSG(buflen <= BUFFER_MAX,
	    "aio_context_init: buffer too large (%d > %d)",
	    buflen, BUFFER_MAX);
	bzero(ac, sizeof(*ac));
	ac->ac_read_fd = read_fd;
	ac->ac_write_fd = write_fd;
	ac->ac_buflen = buflen;
	srandomdev();
	ac->ac_seed = random();
	aio_fill_buffer(ac->ac_buffer, buflen, ac->ac_seed);
	ATF_REQUIRE_MSG(aio_test_buffer(ac->ac_buffer, buflen,
	    ac->ac_seed) != 0, "aio_test_buffer: internal error");
}