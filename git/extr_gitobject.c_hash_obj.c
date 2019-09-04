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
 unsigned int sha1hash (unsigned char const*) ; 

__attribute__((used)) static unsigned int hash_obj(const unsigned char *sha1, unsigned int n)
{
	return sha1hash(sha1) & (n - 1);
}