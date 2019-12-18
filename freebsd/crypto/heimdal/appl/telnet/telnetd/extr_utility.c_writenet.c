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

/* Variables and functions */
 size_t BUFSIZ ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  netflush () ; 
 int /*<<< orphan*/ * netobuf ; 
 int /*<<< orphan*/ * nfrontp ; 

void
writenet(const void *ptr, size_t len)
{
    /* flush buffer if no room for new data) */
    while ((&netobuf[BUFSIZ] - nfrontp) < len) {
	/* if this fails, don't worry, buffer is a little big */
	netflush();
    }
    if ((&netobuf[BUFSIZ] - nfrontp) < len)
	abort();

    memmove(nfrontp, ptr, len);
    nfrontp += len;
}