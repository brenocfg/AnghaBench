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
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ svn_fs_dirent_t ;
typedef  scalar_t__ apr_uint32_t ;
typedef  scalar_t__ apr_size_t ;

/* Variables and functions */
 scalar_t__ APR_ALIGN_DEFAULT (scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_fs__id_serialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_temp_serializer__get_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__push (int /*<<< orphan*/ *,void const* const*,int) ; 

__attribute__((used)) static void
serialize_dir_entry(svn_temp_serializer__context_t *context,
                    svn_fs_dirent_t **entry_p,
                    apr_uint32_t *length)
{
  svn_fs_dirent_t *entry = *entry_p;
  apr_size_t initial_length = svn_temp_serializer__get_length(context);

  svn_temp_serializer__push(context,
                            (const void * const *)entry_p,
                            sizeof(**entry_p));

  svn_fs_fs__id_serialize(context, &entry->id);
  svn_temp_serializer__add_string(context, &entry->name);

  *length = (apr_uint32_t)(  svn_temp_serializer__get_length(context)
                           - APR_ALIGN_DEFAULT(initial_length));

  svn_temp_serializer__pop(context);
}