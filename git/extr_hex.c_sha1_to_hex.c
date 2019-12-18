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
 size_t GIT_HASH_SHA1 ; 
 int /*<<< orphan*/ * hash_algos ; 
 char* hash_to_hex_algop (unsigned char const*,int /*<<< orphan*/ *) ; 

char *sha1_to_hex(const unsigned char *sha1)
{
	return hash_to_hex_algop(sha1, &hash_algos[GIT_HASH_SHA1]);
}