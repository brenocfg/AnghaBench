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
struct TYPE_3__ {int /*<<< orphan*/  number; int /*<<< orphan*/  revision; } ;
typedef  TYPE_1__ svn_fs_fs__id_part_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  locale_independent_strtol (int /*<<< orphan*/ *,char const*,char const**) ; 
 int /*<<< orphan*/  svn__base36toui64 (char const**,char const*) ; 

__attribute__((used)) static svn_boolean_t
txn_id_parse(svn_fs_fs__id_part_t *txn_id,
             const char *data)
{
  const char *end;
  if (!locale_independent_strtol(&txn_id->revision, data, &end))
    return FALSE;

  data = end;
  if (*data != '-')
    return FALSE;

  ++data;
  txn_id->number = svn__base36toui64(&data, data);
  return *data == '\0';
}