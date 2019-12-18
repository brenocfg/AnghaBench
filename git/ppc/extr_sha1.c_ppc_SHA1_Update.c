#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_4__ {unsigned char const* b; } ;
struct TYPE_5__ {int len; int cnt; int /*<<< orphan*/  hash; TYPE_1__ buf; } ;
typedef  TYPE_2__ ppc_SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char const*,unsigned char const*,unsigned long) ; 
 int /*<<< orphan*/  ppc_sha1_core (int /*<<< orphan*/ ,unsigned char const*,unsigned long) ; 

int ppc_SHA1_Update(ppc_SHA_CTX *c, const void *ptr, unsigned long n)
{
	unsigned long nb;
	const unsigned char *p = ptr;

	c->len += (uint64_t) n << 3;
	while (n != 0) {
		if (c->cnt || n < 64) {
			nb = 64 - c->cnt;
			if (nb > n)
				nb = n;
			memcpy(&c->buf.b[c->cnt], p, nb);
			if ((c->cnt += nb) == 64) {
				ppc_sha1_core(c->hash, c->buf.b, 1);
				c->cnt = 0;
			}
		} else {
			nb = n >> 6;
			ppc_sha1_core(c->hash, p, nb);
			nb <<= 6;
		}
		n -= nb;
		p += nb;
	}
	return 0;
}