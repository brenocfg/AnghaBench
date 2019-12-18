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
struct sha384_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ sha384_done (struct sha384_state*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sha384_init (struct sha384_state*) ; 
 scalar_t__ sha384_process (struct sha384_state*,int /*<<< orphan*/  const*,size_t const) ; 

int sha384_vector(size_t num_elem, const u8 *addr[], const size_t *len,
		  u8 *mac)
{
	struct sha384_state ctx;
	size_t i;

	sha384_init(&ctx);
	for (i = 0; i < num_elem; i++)
		if (sha384_process(&ctx, addr[i], len[i]))
			return -1;
	if (sha384_done(&ctx, mac))
		return -1;
	return 0;
}