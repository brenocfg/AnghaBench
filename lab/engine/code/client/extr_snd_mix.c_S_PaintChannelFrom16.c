#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sfx_t ;
typedef  int /*<<< orphan*/  channel_t ;
struct TYPE_2__ {scalar_t__ integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_PaintChannelFrom16_altivec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ; 
 int /*<<< orphan*/  S_PaintChannelFrom16_scalar (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int,int) ; 
 TYPE_1__* com_altivec ; 
 int /*<<< orphan*/  paintbuffer ; 
 int /*<<< orphan*/  snd_vol ; 

__attribute__((used)) static void S_PaintChannelFrom16( channel_t *ch, const sfx_t *sc, int count, int sampleOffset, int bufferOffset ) {
#if idppc_altivec
	if (com_altivec->integer) {
		// must be in a separate translation unit or G3 systems will crash.
		S_PaintChannelFrom16_altivec( paintbuffer, snd_vol, ch, sc, count, sampleOffset, bufferOffset );
		return;
	}
#endif
	S_PaintChannelFrom16_scalar( ch, sc, count, sampleOffset, bufferOffset );
}