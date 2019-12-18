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
typedef  int ag_char_map_mask_t ;

/* Variables and functions */
 int* ag_char_map_table ; 

__attribute__((used)) static inline int
is_ag_char_map_char(char ch, ag_char_map_mask_t mask)
{
    unsigned int ix = (unsigned char)ch;
    return ((ix < 128) && ((ag_char_map_table[ix] & mask) != 0));
}