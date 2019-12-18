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
struct sc_rchinfo {int /*<<< orphan*/  buffer; int /*<<< orphan*/  adc_idx; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHANGE ; 
 int /*<<< orphan*/  M3_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sndbuf_getblksz (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int32_t
m3_rchan_setblocksize(kobj_t kobj, void *chdata, u_int32_t blocksize)
{
	struct sc_rchinfo *ch = chdata;

	M3_DEBUG(CHANGE, ("m3_rchan_setblocksize(adc=%d, blocksize=%d)\n",
			  ch->adc_idx, blocksize));

	return (sndbuf_getblksz(ch->buffer));
}