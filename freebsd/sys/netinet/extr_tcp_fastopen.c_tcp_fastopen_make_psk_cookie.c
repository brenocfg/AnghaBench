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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u_int8_t ;
typedef  int /*<<< orphan*/  SIPHASH_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SipHash24_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SipHash_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SipHash_SetKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SipHash_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
tcp_fastopen_make_psk_cookie(uint8_t *psk, uint8_t *cookie, uint8_t cookie_len)
{
	SIPHASH_CTX ctx;
	uint64_t psk_cookie;

	SipHash24_Init(&ctx);
	SipHash_SetKey(&ctx, psk);
	SipHash_Update(&ctx, cookie, cookie_len);
	SipHash_Final((u_int8_t *)&psk_cookie, &ctx);

	return (psk_cookie);
}