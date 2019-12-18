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
struct fmemopen_cookie {struct fmemopen_cookie* buf; scalar_t__ own; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct fmemopen_cookie*) ; 

__attribute__((used)) static int
fmemopen_close(void *cookie)
{
	struct fmemopen_cookie *ck = cookie;

	if (ck->own)
		free(ck->buf);

	free(ck);

	return (0);
}