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
typedef  int /*<<< orphan*/  tm ;
struct tm {int /*<<< orphan*/  tm_year; } ;
struct TYPE_3__ {int /*<<< orphan*/  tm_year; } ;

/* Variables and functions */
 int /*<<< orphan*/  has_timestamp (char const*) ; 
 TYPE_1__* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* now_tm ; 
 scalar_t__ str_to_time (char const*,char const*,struct tm*) ; 
 scalar_t__ strftime (char*,int,char const*,struct tm*) ; 
 int /*<<< orphan*/ * strpbrk (char const*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timestamp ; 

int
convert_date (char *res, const char *data, const char *from, const char *to,
              int size)
{
  struct tm tm;

  memset (&tm, 0, sizeof (tm));
  timestamp = time (NULL);
  now_tm = localtime (&timestamp);

  if (str_to_time (data, from, &tm) != 0)
    return 1;

  /* if not a timestamp, use current year if not passed */
  if (!has_timestamp (from) && strpbrk (from, "Yy") == NULL)
    tm.tm_year = now_tm->tm_year;

  if (strftime (res, size, to, &tm) <= 0)
    return 1;

  return 0;
}