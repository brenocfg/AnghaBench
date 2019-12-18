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
typedef  int /*<<< orphan*/  platform_SHA_CTX ;

/* Variables and functions */
 size_t SHA1_MAX_BLOCK_SIZE ; 
 int /*<<< orphan*/  platform_SHA1_Update (int /*<<< orphan*/ *,char const*,size_t) ; 

int git_SHA1_Update_Chunked(platform_SHA_CTX *c, const void *data, size_t len)
{
	size_t nr;
	size_t total = 0;
	const char *cdata = (const char*)data;

	while (len) {
		nr = len;
		if (nr > SHA1_MAX_BLOCK_SIZE)
			nr = SHA1_MAX_BLOCK_SIZE;
		platform_SHA1_Update(c, cdata, nr);
		total += nr;
		cdata += nr;
		len -= nr;
	}
	return total;
}