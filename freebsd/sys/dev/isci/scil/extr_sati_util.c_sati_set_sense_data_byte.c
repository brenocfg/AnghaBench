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
typedef  int /*<<< orphan*/  U8 ;
typedef  size_t U32 ;

/* Variables and functions */

void sati_set_sense_data_byte(
   U8  * sense_data,
   U32   max_sense_data_len,
   U32   byte_offset,
   U8    value
)
{
   // Ensure that we don't attempt to write past the end of the sense
   // data buffer.
   if (byte_offset < max_sense_data_len)
      sense_data[byte_offset] = value;
}