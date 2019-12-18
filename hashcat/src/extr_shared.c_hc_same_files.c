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
struct stat {scalar_t__ st_blocks; scalar_t__ st_blksize; scalar_t__ STAT_NANOSECONDS_ACCESS_TIME; scalar_t__ st_atime; scalar_t__ st_rdev; scalar_t__ st_gid; scalar_t__ st_uid; scalar_t__ st_nlink; scalar_t__ st_mode; } ;
typedef  int /*<<< orphan*/  HCFILE ;

/* Variables and functions */
 scalar_t__ fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  hc_fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hc_fileno (int /*<<< orphan*/ *) ; 
 int hc_fopen (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ memcmp (struct stat*,struct stat*,int) ; 

bool hc_same_files (char *file1, char *file2)
{
  if ((file1 != NULL) && (file2 != NULL))
  {
    struct stat tmpstat_file1;
    struct stat tmpstat_file2;

    int do_check = 0;

    HCFILE fp;

    if (hc_fopen (&fp, file1, "r") == true)
    {
      if (fstat (hc_fileno (&fp), &tmpstat_file1))
      {
        hc_fclose (&fp);

        return false;
      }

      hc_fclose (&fp);

      do_check++;
    }

    if (hc_fopen (&fp, file2, "r") == true)
    {
      if (fstat (hc_fileno (&fp), &tmpstat_file2))
      {
        hc_fclose (&fp);

        return false;
      }

      hc_fclose (&fp);

      do_check++;
    }

    if (do_check == 2)
    {
      tmpstat_file1.st_mode     = 0;
      tmpstat_file1.st_nlink    = 0;
      tmpstat_file1.st_uid      = 0;
      tmpstat_file1.st_gid      = 0;
      tmpstat_file1.st_rdev     = 0;
      tmpstat_file1.st_atime    = 0;

      #if defined (STAT_NANOSECONDS_ACCESS_TIME)
      tmpstat_file1.STAT_NANOSECONDS_ACCESS_TIME = 0;
      #endif

      #if defined (_POSIX)
      tmpstat_file1.st_blksize  = 0;
      tmpstat_file1.st_blocks   = 0;
      #endif

      tmpstat_file2.st_mode     = 0;
      tmpstat_file2.st_nlink    = 0;
      tmpstat_file2.st_uid      = 0;
      tmpstat_file2.st_gid      = 0;
      tmpstat_file2.st_rdev     = 0;
      tmpstat_file2.st_atime    = 0;

      #if defined (STAT_NANOSECONDS_ACCESS_TIME)
      tmpstat_file2.STAT_NANOSECONDS_ACCESS_TIME = 0;
      #endif

      #if defined (_POSIX)
      tmpstat_file2.st_blksize  = 0;
      tmpstat_file2.st_blocks   = 0;
      #endif

      if (memcmp (&tmpstat_file1, &tmpstat_file2, sizeof (struct stat)) == 0)
      {
        return true;
      }
    }
  }

  return false;
}