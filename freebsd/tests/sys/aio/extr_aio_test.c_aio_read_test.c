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
struct sigevent {int dummy; } ;
struct aiocb {int aio_nbytes; struct sigevent aio_sigevent; scalar_t__ aio_offset; int /*<<< orphan*/  aio_fildes; struct aiocb* aio_buf; } ;
struct aio_context {int ac_buflen; int /*<<< orphan*/  ac_seed; struct aiocb* ac_buffer; int /*<<< orphan*/  ac_read_fd; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ (* completion ) (struct aiocb*) ;
typedef  int /*<<< orphan*/  aio ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE_EQ_MSG (scalar_t__,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ aio_read (struct aiocb*) ; 
 scalar_t__ aio_test_buffer (struct aiocb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,...) ; 
 int /*<<< orphan*/  bzero (struct aiocb*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aio_read_test(struct aio_context *ac, completion comp, struct sigevent *sev)
{
	struct aiocb aio;
	ssize_t len;

	bzero(ac->ac_buffer, ac->ac_buflen);
	bzero(&aio, sizeof(aio));
	aio.aio_buf = ac->ac_buffer;
	aio.aio_nbytes = ac->ac_buflen;
	aio.aio_fildes = ac->ac_read_fd;
	aio.aio_offset = 0;
	if (sev)
		aio.aio_sigevent = *sev;

	if (aio_read(&aio) < 0)
		atf_tc_fail("aio_read failed: %s", strerror(errno));

	len = comp(&aio);
	if (len < 0)
		atf_tc_fail("aio failed: %s", strerror(errno));

	ATF_REQUIRE_EQ_MSG(len, ac->ac_buflen,
	    "aio short read (%jd)", (intmax_t)len);

	if (aio_test_buffer(ac->ac_buffer, ac->ac_buflen, ac->ac_seed) == 0)
		atf_tc_fail("buffer mismatched");
}