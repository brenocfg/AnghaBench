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
typedef  scalar_t__ uint8_t ;
typedef  unsigned long uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t __onfi_parameter_crc_compute(uint8_t *data)
{
    const int order = 16;                     // Order of the CRC-16
    unsigned long i, j, c, bit;
    unsigned long crc = 0x4F4E;              // Initialize the shift register with 0x4F4E
    unsigned long crcmask = ((((unsigned long)1<<(order-1))-1)<<1)|1;
    unsigned long crchighbit = (unsigned long)1<<(order-1);

    for (i = 0; i < 254; i++)
    {
        c = (unsigned long)data[i];
        for (j = 0x80; j; j >>= 1) {
              bit = crc & crchighbit;
              crc <<= 1;
              if (c & j)
                  bit ^= crchighbit;
              if (bit)
                   crc ^= 0x8005;
        }
        crc &= crcmask;
    }
    return(crc);
}