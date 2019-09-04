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
struct TYPE_4__ {int* b; int /*<<< orphan*/ * l; } ;
struct TYPE_5__ {unsigned int cnt; int /*<<< orphan*/  hash; TYPE_1__ buf; int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ppc_SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppc_sha1_core (int /*<<< orphan*/ ,int*,int) ; 

int ppc_SHA1_Final(unsigned char *hash, ppc_SHA_CTX *c)
{
	unsigned int cnt = c->cnt;

	c->buf.b[cnt++] = 0x80;
	if (cnt > 56) {
		if (cnt < 64)
			memset(&c->buf.b[cnt], 0, 64 - cnt);
		ppc_sha1_core(c->hash, c->buf.b, 1);
		cnt = 0;
	}
	if (cnt < 56)
		memset(&c->buf.b[cnt], 0, 56 - cnt);
	c->buf.l[7] = c->len;
	ppc_sha1_core(c->hash, c->buf.b, 1);
	memcpy(hash, c->hash, 20);
	return 0;
}