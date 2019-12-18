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
typedef  int /*<<< orphan*/  u_int32_t ;
struct via_chinfo {int /*<<< orphan*/  blksz; int /*<<< orphan*/  buffer; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEGS_PER_CHAN ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
viachan_setblocksize(kobj_t obj, void *data, u_int32_t blocksize)
{
	struct via_chinfo *ch = data;

	ch->blksz = blocksize;
	sndbuf_resize(ch->buffer, SEGS_PER_CHAN, ch->blksz);

	return ch->blksz;
}