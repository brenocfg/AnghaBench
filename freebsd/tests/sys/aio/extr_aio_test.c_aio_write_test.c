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
struct aiocb {scalar_t__ aio_nbytes; struct sigevent aio_sigevent; scalar_t__ aio_offset; int /*<<< orphan*/  aio_fildes; int /*<<< orphan*/  aio_buf; } ;
struct aio_context {scalar_t__ ac_buflen; int /*<<< orphan*/  ac_write_fd; int /*<<< orphan*/  ac_buffer; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  scalar_t__ (* completion ) (struct aiocb*) ;
typedef  int /*<<< orphan*/  aio ;

/* Variables and functions */
 scalar_t__ aio_write (struct aiocb*) ; 
 int /*<<< orphan*/  atf_tc_fail (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct aiocb*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
aio_write_test(struct aio_context *ac, completion comp, struct sigevent *sev)
{
	struct aiocb aio;
	ssize_t len;

	bzero(&aio, sizeof(aio));
	aio.aio_buf = ac->ac_buffer;
	aio.aio_nbytes = ac->ac_buflen;
	aio.aio_fildes = ac->ac_write_fd;
	aio.aio_offset = 0;
	if (sev)
		aio.aio_sigevent = *sev;

	if (aio_write(&aio) < 0)
		atf_tc_fail("aio_write failed: %s", strerror(errno));

	len = comp(&aio);
	if (len < 0)
		atf_tc_fail("aio failed: %s", strerror(errno));

	if (len != ac->ac_buflen)
		atf_tc_fail("aio short write (%jd)", (intmax_t)len);
}