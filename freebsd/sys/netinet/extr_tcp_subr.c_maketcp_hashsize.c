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
 int fls (int) ; 

__attribute__((used)) static int
maketcp_hashsize(int size)
{
	int hashsize;

	/*
	 * auto tune.
	 * get the next power of 2 higher than maxsockets.
	 */
	hashsize = 1 << fls(size);
	/* catch overflow, and just go one power of 2 smaller */
	if (hashsize < size) {
		hashsize = 1 << (fls(size) - 1);
	}
	return (hashsize);
}