#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct header {int magic; int sect; int ord; void* datachk; void* hdrchk; scalar_t__* labels; int /*<<< orphan*/  track; } ;
struct TYPE_6__ {scalar_t__ trackbuf; TYPE_2__* type; TYPE_1__* dtype; int /*<<< orphan*/  track; } ;
struct TYPE_5__ {int sect_mult; } ;
struct TYPE_4__ {int sects; } ;

/* Variables and functions */
 void* checksum (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  encode_block (unsigned long*,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* unit ; 

__attribute__((used)) static unsigned long *putsec(int disk, unsigned long *raw, int cnt)
{
	struct header hdr;
	int i;

	disk&=3;
	*raw = (raw[-1]&1) ? 0x2AAAAAAA : 0xAAAAAAAA;
	raw++;
	*raw++ = 0x44894489;

	hdr.magic = 0xFF;
	hdr.track = unit[disk].track;
	hdr.sect = cnt;
	hdr.ord = unit[disk].dtype->sects * unit[disk].type->sect_mult - cnt;
	for (i = 0; i < 16; i++)
		hdr.labels[i] = 0;
	hdr.hdrchk = checksum((ulong *)&hdr,
			      (char *)&hdr.hdrchk-(char *)&hdr);
	hdr.datachk = checksum((ulong *)(unit[disk].trackbuf+cnt*512), 512);

	encode_block(raw, (ulong *)&hdr.magic, 4);
	raw += 2;
	encode_block(raw, (ulong *)&hdr.labels, 16);
	raw += 8;
	encode_block(raw, (ulong *)&hdr.hdrchk, 4);
	raw += 2;
	encode_block(raw, (ulong *)&hdr.datachk, 4);
	raw += 2;
	encode_block(raw, (ulong *)(unit[disk].trackbuf+cnt*512), 512);
	raw += 256;

	return raw;
}