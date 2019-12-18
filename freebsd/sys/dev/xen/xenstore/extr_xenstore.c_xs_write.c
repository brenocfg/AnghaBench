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
struct xs_transaction {int dummy; } ;
struct sbuf {int dummy; } ;
struct iovec {scalar_t__ iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  XS_WRITE ; 
 scalar_t__ sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 scalar_t__ sbuf_len (struct sbuf*) ; 
 scalar_t__ strlen (char const*) ; 
 struct sbuf* xs_join (char const*,char const*) ; 
 int xs_talkv (struct xs_transaction,int /*<<< orphan*/ ,struct iovec*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
xs_write(struct xs_transaction t, const char *dir, const char *node,
    const char *string)
{
	struct sbuf *path;
	struct iovec iovec[2];
	int error;

	path = xs_join(dir, node);

	iovec[0].iov_base = (void *)(uintptr_t) sbuf_data(path);
	iovec[0].iov_len = sbuf_len(path) + 1;
	iovec[1].iov_base = (void *)(uintptr_t) string;
	iovec[1].iov_len = strlen(string);

	error = xs_talkv(t, XS_WRITE, iovec, 2, NULL, NULL);
	sbuf_delete(path);

	return (error);
}