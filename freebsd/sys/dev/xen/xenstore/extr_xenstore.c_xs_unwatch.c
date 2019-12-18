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
struct iovec {void* iov_len; void* iov_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  XST_NIL ; 
 int /*<<< orphan*/  XS_UNWATCH ; 
 void* strlen (char const*) ; 
 int xs_talkv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iovec*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
xs_unwatch(const char *path, const char *token)
{
	struct iovec iov[2];

	iov[0].iov_base = (void *)(uintptr_t) path;
	iov[0].iov_len = strlen(path) + 1;
	iov[1].iov_base = (void *)(uintptr_t) token;
	iov[1].iov_len = strlen(token) + 1;

	return (xs_talkv(XST_NIL, XS_UNWATCH, iov, 2, NULL, NULL));
}