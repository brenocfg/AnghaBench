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
typedef  int uint32_t ;
struct bge_softc {int dummy; } ;

/* Variables and functions */
 int BGE_MODECTL_BYTESWAP_DATA ; 
 int BGE_MODECTL_BYTESWAP_NONFRAME ; 
 int BGE_MODECTL_WORDSWAP_DATA ; 
 int BGE_MODECTL_WORDSWAP_NONFRAME ; 

__attribute__((used)) static uint32_t
bge_dma_swap_options(struct bge_softc *sc)
{
	uint32_t dma_options;

	dma_options = BGE_MODECTL_WORDSWAP_NONFRAME |
	    BGE_MODECTL_BYTESWAP_DATA | BGE_MODECTL_WORDSWAP_DATA;
#if BYTE_ORDER == BIG_ENDIAN
	dma_options |= BGE_MODECTL_BYTESWAP_NONFRAME;
#endif
	return (dma_options);
}