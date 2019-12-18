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
struct skcipher_walk {int flags; int /*<<< orphan*/  out; scalar_t__ alignmask; scalar_t__ buffer; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,scalar_t__) ; 
 int SKCIPHER_WALK_PHYS ; 
 int /*<<< orphan*/  scatterwalk_copychunks (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/ * skcipher_get_spot (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int skcipher_done_slow(struct skcipher_walk *walk, unsigned int bsize)
{
	u8 *addr;

	addr = (u8 *)ALIGN((unsigned long)walk->buffer, walk->alignmask + 1);
	addr = skcipher_get_spot(addr, bsize);
	scatterwalk_copychunks(addr, &walk->out, bsize,
			       (walk->flags & SKCIPHER_WALK_PHYS) ? 2 : 1);
	return 0;
}