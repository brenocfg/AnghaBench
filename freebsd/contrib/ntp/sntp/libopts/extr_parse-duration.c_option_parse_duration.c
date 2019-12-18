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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  BAD_TIME ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  parse_non_iso8601 (char const*) ; 
 int /*<<< orphan*/  parse_period (char const*) ; 
 int /*<<< orphan*/  parse_time (char const*) ; 

time_t
parse_duration (char const * pz)
{
  while (isspace ((unsigned char)*pz))
    pz++;

  switch (*pz)
    {
    case 'P':
      return parse_period (pz + 1);

    case 'T':
      return parse_time (pz + 1);

    default:
      if (isdigit ((unsigned char)*pz))
        return parse_non_iso8601 (pz);

      errno = EINVAL;
      return BAD_TIME;
    }
}