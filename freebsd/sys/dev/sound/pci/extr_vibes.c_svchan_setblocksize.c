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
struct sc_info {int bufsz; } ;
struct sc_chinfo {int /*<<< orphan*/  buffer; struct sc_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RANGE (int,int /*<<< orphan*/ ,int) ; 
 int SV_INTR_PER_BUFFER ; 
 int /*<<< orphan*/  SV_MIN_BLKSZ ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  sndbuf_resize (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u_int32_t
svchan_setblocksize(kobj_t obj, void *data, u_int32_t blocksize)
{
	struct sc_chinfo *ch = data;
	struct sc_info *sc = ch->parent;

        /* user has requested interrupts every blocksize bytes */
	RANGE(blocksize, SV_MIN_BLKSZ, sc->bufsz / SV_INTR_PER_BUFFER);
	sndbuf_resize(ch->buffer, SV_INTR_PER_BUFFER, blocksize);
	DEB(printf("svchan_setblocksize: %d\n", blocksize));
	return blocksize;
}