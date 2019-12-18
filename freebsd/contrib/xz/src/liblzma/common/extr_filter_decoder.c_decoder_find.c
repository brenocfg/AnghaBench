#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ lzma_vli ;
struct TYPE_5__ {scalar_t__ id; } ;
typedef  TYPE_1__ lzma_filter_decoder ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__ const*) ; 
 TYPE_1__ const* decoders ; 

__attribute__((used)) static const lzma_filter_decoder *
decoder_find(lzma_vli id)
{
	for (size_t i = 0; i < ARRAY_SIZE(decoders); ++i)
		if (decoders[i].id == id)
			return decoders + i;

	return NULL;
}