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
struct rwcount {int /*<<< orphan*/  read; int /*<<< orphan*/  fd; } ;
typedef  int ev_ssize_t ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 struct rwcount* BIO_get_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_retry_read (int /*<<< orphan*/ *) ; 
 scalar_t__ EVUTIL_ERR_RW_RETRIABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVUTIL_SOCKET_ERROR () ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bio_rwcount_read(BIO *b, char *out, int outlen)
{
	struct rwcount *rw = BIO_get_data(b);
	ev_ssize_t ret = recv(rw->fd, out, outlen, 0);
	++rw->read;
	if (ret == -1 && EVUTIL_ERR_RW_RETRIABLE(EVUTIL_SOCKET_ERROR())) {
		BIO_set_retry_read(b);
	}
	return ret;
}