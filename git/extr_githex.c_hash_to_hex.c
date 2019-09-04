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

/* Variables and functions */
 char* hash_to_hex_algop (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_hash_algo ; 

char *hash_to_hex(const unsigned char *hash)
{
	return hash_to_hex_algop(hash, the_hash_algo);
}