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
typedef  char cch_t ;

/* Variables and functions */
 int strtoul (char*,char**,int) ; 

__attribute__((used)) static unsigned long
str_const_to_ul (cch_t * str, cch_t ** ppz, int base)
{
  char * pz;
  int rv = strtoul (str, &pz, base);
  *ppz = pz;
  return rv;
}