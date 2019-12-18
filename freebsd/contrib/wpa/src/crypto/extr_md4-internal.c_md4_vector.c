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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  MD4_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  MD4Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD4Update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 
 scalar_t__ TEST_FAIL () ; 

int md4_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
	MD4_CTX ctx;
	size_t i;

	if (TEST_FAIL())
		return -1;

	MD4Init(&ctx);
	for (i = 0; i < num_elem; i++)
		MD4Update(&ctx, addr[i], len[i]);
	MD4Final(mac, &ctx);
	return 0;
}