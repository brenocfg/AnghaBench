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
typedef  scalar_t__ u_char ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EMSGSIZE ; 
 int /*<<< orphan*/  SPRINTF (char*) ; 
 size_t decoct (scalar_t__ const*,size_t,char*,size_t) ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static char *
inet_cidr_ntop_ipv4(const u_char *src, int bits, char *dst, size_t size) {
	char *odst = dst;
	size_t len = 4;
	size_t b;
	size_t bytes;

	if ((bits < -1) || (bits > 32)) {
		errno = EINVAL;
		return (NULL);
	}

	/* Find number of significant bytes in address. */
	if (bits == -1)
		len = 4;
	else
		for (len = 1, b = 1 ; b < 4U; b++)
			if (*(src + b))
				len = b + 1;

	/* Format whole octets plus nonzero trailing octets. */
	bytes = (((bits <= 0) ? 1 : bits) + 7) / 8;
	if (len > bytes)
		bytes = len;
	b = decoct(src, bytes, dst, size);
	if (b == 0U)
		goto emsgsize;
	dst += b;
	size -= b;

	if (bits != -1) {
		/* Format CIDR /width. */
		if (size < sizeof "/32")
			goto emsgsize;
		dst += SPRINTF((dst, "/%u", bits));
	}

	return (odst);

 emsgsize:
	errno = EMSGSIZE;
	return (NULL);
}