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
struct sha256_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ TEST_FAIL () ; 
 scalar_t__ sha256_done (struct sha256_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha256_init (struct sha256_state*) ; 
 scalar_t__ sha256_process (struct sha256_state*,int /*<<< orphan*/  const*,size_t const) ; 

int sha256_vector(size_t num_elem, const u8 *addr[], const size_t *len,
		  u8 *mac)
{
	struct sha256_state ctx;
	size_t i;

	if (TEST_FAIL())
		return -1;

	sha256_init(&ctx);
	for (i = 0; i < num_elem; i++)
		if (sha256_process(&ctx, addr[i], len[i]))
			return -1;
	if (sha256_done(&ctx, mac))
		return -1;
	return 0;
}