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
typedef  int u_int32_t ;
struct sc_pchinfo {int spd; int /*<<< orphan*/  buffer; struct sc_info* parent; } ;
struct sc_info {int bufsz; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int DS1_IRQHZ ; 
 int roundup2 (int,int) ; 
 int sndbuf_getalign (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u_int32_t
ds1pchan_setblocksize(kobj_t obj, void *data, u_int32_t blocksize)
{
	struct sc_pchinfo *ch = data;
	struct sc_info *sc = ch->parent;
	int drate;

	/* irq rate is fixed at 187.5hz */
	drate = ch->spd * sndbuf_getalign(ch->buffer);
	blocksize = roundup2((drate << 8) / DS1_IRQHZ, 4);
	sndbuf_resize(ch->buffer, sc->bufsz / blocksize, blocksize);

	return blocksize;
}