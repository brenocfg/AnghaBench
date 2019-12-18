#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {scalar_t__ STAT_NANOSECONDS_ACCESS_TIME; scalar_t__ st_atime; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat; int /*<<< orphan*/  encoding_to; int /*<<< orphan*/  encoding_from; } ;
typedef  TYPE_1__ dictstat_t ;

/* Variables and functions */
 int memcmp (struct stat*,struct stat*,int) ; 
 int /*<<< orphan*/  memcpy (struct stat*,int /*<<< orphan*/ *,int) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sort_by_dictstat (const void *s1, const void *s2)
{
  const dictstat_t *d1 = (const dictstat_t *) s1;
  const dictstat_t *d2 = (const dictstat_t *) s2;

  const int rc_from = strcmp (d1->encoding_from, d2->encoding_from);

  if (rc_from != 0) return rc_from;

  const int rc_to = strcmp (d1->encoding_to, d2->encoding_to);

  if (rc_to != 0) return rc_to;

  struct stat stat1;
  struct stat stat2;

  memcpy (&stat1, &d1->stat, sizeof (struct stat));
  memcpy (&stat2, &d2->stat, sizeof (struct stat));

  stat1.st_atime = 0;
  stat2.st_atime = 0;

  #if defined (STAT_NANOSECONDS_ACCESS_TIME)
  stat1.STAT_NANOSECONDS_ACCESS_TIME = 0;
  stat2.STAT_NANOSECONDS_ACCESS_TIME = 0;
  #endif

  const int rc_memcmp = memcmp (&stat1, &stat2, sizeof (struct stat));

  return rc_memcmp;
}