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
struct rwcount {int /*<<< orphan*/  write; int /*<<< orphan*/  fd; } ;
typedef  int ev_ssize_t ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 struct rwcount* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_write (int /*<<< orphan*/ *) ; 
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVUTIL_SOCKET_ERROR () ; 
 int send (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bio_rwcount_write(BIO *b, const char *in, int inlen)
{
	struct rwcount *rw = BIO_get_data(b);
	ev_ssize_t ret = send(rw->fd, in, inlen, 0);
	++rw->write;
	if (ret == -1 && EVUTIL_ERR_RW_RETRIABLE(EVUTIL_SOCKET_ERROR())) {
		BIO_set_retry_write(b);
	}
	return ret;
}