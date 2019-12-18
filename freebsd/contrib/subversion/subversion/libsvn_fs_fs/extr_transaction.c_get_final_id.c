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
typedef  scalar_t__ svn_revnum_t ;
struct TYPE_3__ {scalar_t__ revision; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ svn_fs_fs__id_part_t ;
typedef  scalar_t__ apr_uint64_t ;

/* Variables and functions */
 int SVN_FS_FS__MIN_NO_GLOBAL_IDS_FORMAT ; 
 scalar_t__ SVN_INVALID_REVNUM ; 

__attribute__((used)) static void
get_final_id(svn_fs_fs__id_part_t *part,
             svn_revnum_t revision,
             apr_uint64_t start_id,
             int format)
{
  if (part->revision == SVN_INVALID_REVNUM)
    {
      if (format >= SVN_FS_FS__MIN_NO_GLOBAL_IDS_FORMAT)
        {
          part->revision = revision;
        }
      else
        {
          part->revision = 0;
          part->number += start_id;
        }
    }
}