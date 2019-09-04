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
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline int skip_prefix_mem(const char *buf, size_t len,
				  const char *prefix,
				  const char **out, size_t *outlen)
{
	size_t prefix_len = strlen(prefix);
	if (prefix_len <= len && !memcmp(buf, prefix, prefix_len)) {
		*out = buf + prefix_len;
		*outlen = len - prefix_len;
		return 1;
	}
	return 0;
}