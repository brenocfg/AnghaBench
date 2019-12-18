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
typedef  int /*<<< orphan*/  reg_syntax_t ;

/* Variables and functions */
 int case_fold ; 
 unsigned char eolbyte ; 
 int /*<<< orphan*/  syntax_bits ; 
 int syntax_bits_set ; 

void
dfasyntax (reg_syntax_t bits, int fold, unsigned char eol)
{
  syntax_bits_set = 1;
  syntax_bits = bits;
  case_fold = fold;
  eolbyte = eol;
}