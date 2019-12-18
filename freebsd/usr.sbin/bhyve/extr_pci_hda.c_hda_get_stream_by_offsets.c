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
typedef  int uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int HDA_IOSS_NO ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static inline uint8_t
hda_get_stream_by_offsets(uint32_t offset, uint8_t reg_offset)
{
	uint8_t stream_ind = (offset - reg_offset) >> 5;

	assert(stream_ind < HDA_IOSS_NO);

	return (stream_ind);
}