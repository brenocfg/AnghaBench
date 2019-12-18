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
typedef  scalar_t__ whats_done_t ;
typedef  scalar_t__ time_t ;
typedef  char cch_t ;

/* Variables and functions */
 scalar_t__ BAD_TIME ; 
 scalar_t__ DAY_IS_DONE ; 
 scalar_t__ EINVAL ; 
 scalar_t__ HOUR_IS_DONE ; 
 scalar_t__ MINUTE_IS_DONE ; 
 scalar_t__ MONTH_IS_DONE ; 
 scalar_t__ NOTHING_IS_DONE ; 
#define  NUL 128 
 scalar_t__ SECOND_IS_DONE ; 
 unsigned int SEC_PER_DAY ; 
 scalar_t__ SEC_PER_HR ; 
 unsigned int SEC_PER_MIN ; 
 unsigned int SEC_PER_MONTH ; 
 unsigned int SEC_PER_WEEK ; 
 unsigned int SEC_PER_YEAR ; 
 scalar_t__ WEEK_IS_DONE ; 
 scalar_t__ YEAR_IS_DONE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ parse_hr_min_sec (scalar_t__,char*) ; 
 scalar_t__ scale_n_add (scalar_t__,scalar_t__,unsigned int) ; 
 scalar_t__ str_const_to_l (char*,char**,int) ; 

__attribute__((used)) static time_t
parse_non_iso8601 (cch_t * pz)
{
  whats_done_t whatd_we_do = NOTHING_IS_DONE;

  time_t res = 0;

  do  {
    time_t val;

    errno = 0;
    val = str_const_to_l (pz, &pz, 10);
    if (errno != 0)
      goto bad_time;

    /*  IF we find a colon, then we're going to have a seconds value.
        We will not loop here any more.  We cannot already have parsed
        a minute value and if we've parsed an hour value, then the result
        value has to be less than an hour. */
    if (*pz == ':')
      {
        if (whatd_we_do >= MINUTE_IS_DONE)
          break;

        val = parse_hr_min_sec (val, pz);

        if ((whatd_we_do == HOUR_IS_DONE) && (val >= SEC_PER_HR))
          break;

        return scale_n_add (res, val, 1);
      }

    {
      unsigned int mult;

      /*  Skip over white space following the number we just parsed. */
      while (isspace ((unsigned char)*pz))
        pz++;

      switch (*pz)
        {
        default:  goto bad_time;
        case NUL:
          return scale_n_add (res, val, 1);

        case 'y': case 'Y':
          if (whatd_we_do >= YEAR_IS_DONE)
            goto bad_time;
          mult = SEC_PER_YEAR;
          whatd_we_do = YEAR_IS_DONE;
          break;

        case 'M':
          if (whatd_we_do >= MONTH_IS_DONE)
            goto bad_time;
          mult = SEC_PER_MONTH;
          whatd_we_do = MONTH_IS_DONE;
          break;

        case 'W':
          if (whatd_we_do >= WEEK_IS_DONE)
            goto bad_time;
          mult = SEC_PER_WEEK;
          whatd_we_do = WEEK_IS_DONE;
          break;

        case 'd': case 'D':
          if (whatd_we_do >= DAY_IS_DONE)
            goto bad_time;
          mult = SEC_PER_DAY;
          whatd_we_do = DAY_IS_DONE;
          break;

        case 'h':
          if (whatd_we_do >= HOUR_IS_DONE)
            goto bad_time;
          mult = SEC_PER_HR;
          whatd_we_do = HOUR_IS_DONE;
          break;

        case 'm':
          if (whatd_we_do >= MINUTE_IS_DONE)
            goto bad_time;
          mult = SEC_PER_MIN;
          whatd_we_do = MINUTE_IS_DONE;
          break;

        case 's':
          mult = 1;
          whatd_we_do = SECOND_IS_DONE;
          break;
        }

      res = scale_n_add (res, val, mult);

      pz++;
      while (isspace ((unsigned char)*pz))
        pz++;
      if (*pz == NUL)
        return res;

      if (! isdigit ((unsigned char)*pz))
        break;
    }

  } while (whatd_we_do < SECOND_IS_DONE);

 bad_time:
  errno = EINVAL;
  return BAD_TIME;
}