#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int pcre_uint8 ;
typedef  unsigned int pcre_uint32 ;
struct TYPE_3__ {int* cbits; } ;
typedef  TYPE_1__ compile_data ;

/* Variables and functions */

__attribute__((used)) static void
set_nottype_bits(pcre_uint8 *start_bits, int cbit_type, unsigned int table_limit,
  compile_data *cd)
{
register pcre_uint32 c;
for (c = 0; c < table_limit; c++) start_bits[c] |= ~cd->cbits[c+cbit_type];
#if defined SUPPORT_UTF && defined COMPILE_PCRE8
if (table_limit != 32) for (c = 24; c < 32; c++) start_bits[c] = 0xff;
#endif
}