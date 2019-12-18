#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int U32 ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_4__ {int logical_block_size; } ;
typedef  int /*<<< orphan*/  TRIM_PAIR ;
typedef  TYPE_2__ SATI_TRANSLATOR_SEQUENCE_T ;

/* Variables and functions */

U32 sati_unmap_calculate_dsm_blocks(
   SATI_TRANSLATOR_SEQUENCE_T * sequence,
   U32                          dsm_descriptor_count
)
{
   U32 blocks = (dsm_descriptor_count * sizeof(TRIM_PAIR))/sequence->device->logical_block_size;
   if ((dsm_descriptor_count * sizeof(TRIM_PAIR)) % sequence->device->logical_block_size)
   {
       blocks++;
   }
   return blocks;
}