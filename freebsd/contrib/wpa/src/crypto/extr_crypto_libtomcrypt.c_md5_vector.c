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
 int /*<<< orphan*/  md5_done (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md5_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md5_process (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t const) ; 

int md5_vector(size_t num_elem, const u8 *addr[], const size_t *len, u8 *mac)
{
	hash_state md;
	size_t i;

	md5_init(&md);
	for (i = 0; i < num_elem; i++)
		md5_process(&md, addr[i], len[i]);
	md5_done(&md, mac);
	return 0;
}