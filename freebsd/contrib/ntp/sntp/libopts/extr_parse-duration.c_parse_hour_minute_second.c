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
typedef  int /*<<< orphan*/  cch_t ;

/* Variables and functions */
 scalar_t__ BAD_TIME ; 
 int /*<<< orphan*/  EINVAL ; 
 int SEC_PER_HR ; 
 int SEC_PER_MIN ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ parse_scaled_value (scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ *,char) ; 
 int strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static time_t
parse_hour_minute_second (cch_t * pz, cch_t * ps)
{
  time_t res = 0;

  res = parse_scaled_value (0, &pz, ps, SEC_PER_HR);

  pz++;
  ps = strchr (pz, ':');
  if (ps == NULL)
    {
      errno = EINVAL;
      return BAD_TIME;
    }

  res = parse_scaled_value (res, &pz, ps, SEC_PER_MIN);

  pz++;
  ps = pz + strlen (pz);
  return parse_scaled_value (res, &pz, ps, 1);
}