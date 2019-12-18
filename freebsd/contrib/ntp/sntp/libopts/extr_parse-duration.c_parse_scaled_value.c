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
typedef  scalar_t__ time_t ;
typedef  scalar_t__ cch_t ;

/* Variables and functions */
 scalar_t__ BAD_TIME ; 
 scalar_t__ EINVAL ; 
 scalar_t__ errno ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ scale_n_add (scalar_t__,scalar_t__,int) ; 
 scalar_t__ str_const_to_ul (scalar_t__*,scalar_t__**,int) ; 

__attribute__((used)) static time_t
parse_scaled_value (time_t base, cch_t ** ppz, cch_t * endp, int scale)
{
  cch_t * pz = *ppz;
  time_t val;

  if (base == BAD_TIME)
    return base;

  errno = 0;
  val = str_const_to_ul (pz, &pz, 10);
  if (errno != 0)
    return BAD_TIME;
  while (isspace ((unsigned char)*pz))
    pz++;
  if (pz != endp)
    {
      errno = EINVAL;
      return BAD_TIME;
    }

  *ppz = pz;
  return scale_n_add (base, val, scale);
}