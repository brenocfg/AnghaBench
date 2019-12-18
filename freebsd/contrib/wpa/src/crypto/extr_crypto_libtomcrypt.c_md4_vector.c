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
typedef  int /*<<< orphan*/  hash_state ;

/* Variables and functions */
 int /*<<< orphan*/  md4_done (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md4_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md4_process (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 

int md4_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
	hash_state md;
	size_t i;

	md4_init(&md);
	for (i = 0; i < num_elem; i++)
		md4_process(&md, addr[i], len[i]);
	md4_done(&md, mac);
	return 0;
}