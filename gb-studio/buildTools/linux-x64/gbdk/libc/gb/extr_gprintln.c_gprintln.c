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
typedef  size_t UINT16 ;
typedef  scalar_t__ INT8 ;
typedef  size_t INT16 ;

/* Variables and functions */
 scalar_t__ UNSIGNED ; 
 char* digits ; 
 int /*<<< orphan*/  wrtchr (char) ; 

void gprintln(INT16 number, INT8 radix, INT8 signed_value)
{
  UINT16 l;

  if(number < 0 && signed_value) {
    wrtchr('-');
    number = -number;
  }
  if((l = (UINT16)number / (UINT16)radix) != 0)
    gprintln(l, radix, UNSIGNED);
  wrtchr(digits[(UINT16)number % (UINT16)radix]);
}