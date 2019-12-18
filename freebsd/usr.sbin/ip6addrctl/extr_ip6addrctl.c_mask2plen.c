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
typedef  int u_char ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_addr; } ;

/* Variables and functions */

__attribute__((used)) static int
mask2plen(struct sockaddr_in6 *mask)
{
	int masklen, final = 0;
	u_char *p, *lim;

	masklen = 0;
	lim = (u_char *)(mask + 1);
	for (p = (u_char *)(&mask->sin6_addr); p < lim; p++) {
		if (final && *p) {
			goto bad;
		}

		switch (*p & 0xff) {
		case 0xff:
			masklen += 8;
			break;
		case 0xfe:
			masklen += 7;
			final++;
			break;
		case 0xfc:
			masklen += 6;
			final++;
			break;
		case 0xf8:
			masklen += 5;
			final++;
			break;
		case 0xf0:
			masklen += 4;
			final++;
			break;
		case 0xe0:
			masklen += 3;
			final++;
			break;
		case 0xc0:
			masklen += 2;
			final++;
			break;
		case 0x80:
			masklen += 1;
			final++;
			break;
		case 0x00:
			final++;
			break;
		default:
			goto bad;
			break;
		}
	}
	return(masklen);

  bad:
	return(-1);
}