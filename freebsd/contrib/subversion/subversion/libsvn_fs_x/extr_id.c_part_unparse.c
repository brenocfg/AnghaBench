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
struct TYPE_3__ {int /*<<< orphan*/  change_set; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ svn_fs_x__id_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn__ui64tobase36 (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
part_unparse(char *p,
             const svn_fs_x__id_t *part)
{
  p += svn__ui64tobase36(p, part->number);
  if (part->change_set >= 0)
    {
      *(p++) = '+';
      p += svn__ui64tobase36(p, part->change_set);
    }
  else
    {
      *(p++) = '-';
      p += svn__ui64tobase36(p, -part->change_set);
    }

  return p;
}