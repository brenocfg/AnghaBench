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
typedef  int /*<<< orphan*/  SHA1_CTX ;

/* Variables and functions */
 unsigned long INT_MAX ; 
 int /*<<< orphan*/  SHA1DCUpdate (int /*<<< orphan*/ *,char const*,unsigned long) ; 

void git_SHA1DCUpdate(SHA1_CTX *ctx, const void *vdata, unsigned long len)
{
	const char *data = vdata;
	/* We expect an unsigned long, but sha1dc only takes an int */
	while (len > INT_MAX) {
		SHA1DCUpdate(ctx, data, INT_MAX);
		data += INT_MAX;
		len -= INT_MAX;
	}
	SHA1DCUpdate(ctx, data, len);
}