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
 int BLOCKSIZE ; 
 int RECORDSIZE ; 
 scalar_t__ block ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int offset ; 
 int /*<<< orphan*/  write_or_die (int,scalar_t__,int) ; 

__attribute__((used)) static void write_trailer(void)
{
	int tail = BLOCKSIZE - offset;
	memset(block + offset, 0, tail);
	write_or_die(1, block, BLOCKSIZE);
	if (tail < 2 * RECORDSIZE) {
		memset(block, 0, offset);
		write_or_die(1, block, BLOCKSIZE);
	}
}