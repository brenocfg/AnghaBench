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
struct TYPE_3__ {scalar_t__ revision; void* number; } ;
typedef  TYPE_1__ svn_fs_fs__id_part_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 scalar_t__ SVN_INVALID_REVNUM ; 
 int TRUE ; 
 int locale_independent_strtol (scalar_t__*,char const*,char const**) ; 
 void* svn__base36toui64 (char const**,char const*) ; 

__attribute__((used)) static svn_boolean_t
part_parse(svn_fs_fs__id_part_t *part,
           const char *data)
{
  const char *end;

  /* special case: ID inside some transaction */
  if (data[0] == '_')
    {
      part->revision = SVN_INVALID_REVNUM;
      part->number = svn__base36toui64(&data, data + 1);
      return *data == '\0';
    }

  /* special case: 0 / default ID */
  if (data[0] == '0' && data[1] == '\0')
    {
      part->revision = 0;
      part->number = 0;
      return TRUE;
    }

  /* read old style / new style ID */
  part->number = svn__base36toui64(&data, data);
  if (data[0] != '-')
    {
      part->revision = 0;
      return *data == '\0';
    }

  return locale_independent_strtol(&part->revision, data+1, &end);
}