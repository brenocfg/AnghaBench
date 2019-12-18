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
typedef  int /*<<< orphan*/  hash_data ;

/* Variables and functions */
 int /*<<< orphan*/  VEC_ADD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forbidden_digests ; 

void
ve_forbidden_digest_add(hash_data *digest, size_t num)
{
	while (num--)
		VEC_ADD(forbidden_digests, digest[num]);
}