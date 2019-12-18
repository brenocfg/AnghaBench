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
struct quoting_options {int* quote_these_too; } ;

/* Variables and functions */
 unsigned char INT_BITS ; 
 struct quoting_options default_quoting_options ; 

int
set_char_quoting (struct quoting_options *o, char c, int i)
{
  unsigned char uc = c;
  int *p = (o ? o : &default_quoting_options)->quote_these_too + uc / INT_BITS;
  int shift = uc % INT_BITS;
  int r = (*p >> shift) & 1;
  *p ^= ((i & 1) ^ r) << shift;
  return r;
}