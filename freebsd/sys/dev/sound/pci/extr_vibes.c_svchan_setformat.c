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
struct sc_chinfo {int /*<<< orphan*/  fmt; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AFMT_16BIT ; 
 int AFMT_CHANNEL (int) ; 
 int /*<<< orphan*/  SV_AFMT_MONO ; 
 int /*<<< orphan*/  SV_AFMT_S16 ; 
 int /*<<< orphan*/  SV_AFMT_STEREO ; 
 int /*<<< orphan*/  SV_AFMT_U8 ; 

__attribute__((used)) static int
svchan_setformat(kobj_t obj, void *data, u_int32_t format)
{
	struct sc_chinfo *ch = data;
	/* NB Just note format here as setting format register
	 * generates noise if dma channel is inactive. */
	ch->fmt  = (AFMT_CHANNEL(format) > 1) ? SV_AFMT_STEREO : SV_AFMT_MONO;
	ch->fmt |= (format & AFMT_16BIT) ? SV_AFMT_S16 : SV_AFMT_U8;
	return 0;
}