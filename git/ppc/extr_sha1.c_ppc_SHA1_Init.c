#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* hash; scalar_t__ cnt; scalar_t__ len; } ;
typedef  TYPE_1__ ppc_SHA_CTX ;

/* Variables and functions */

int ppc_SHA1_Init(ppc_SHA_CTX *c)
{
	c->hash[0] = 0x67452301;
	c->hash[1] = 0xEFCDAB89;
	c->hash[2] = 0x98BADCFE;
	c->hash[3] = 0x10325476;
	c->hash[4] = 0xC3D2E1F0;
	c->len = 0;
	c->cnt = 0;
	return 0;
}