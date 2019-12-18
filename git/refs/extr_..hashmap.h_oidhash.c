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
struct object_id {int /*<<< orphan*/  hash; } ;
typedef  int /*<<< orphan*/  hash ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned int oidhash(const struct object_id *oid)
{
	/*
	 * Equivalent to 'return *(unsigned int *)oid->hash;', but safe on
	 * platforms that don't support unaligned reads.
	 */
	unsigned int hash;
	memcpy(&hash, oid->hash, sizeof(hash));
	return hash;
}