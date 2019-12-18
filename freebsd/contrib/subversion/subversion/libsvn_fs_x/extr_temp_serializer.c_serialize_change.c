#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct TYPE_5__ {int /*<<< orphan*/  copyfrom_path; TYPE_1__ path; } ;
typedef  TYPE_2__ svn_fs_x__change_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_temp_serializer__add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__push (int /*<<< orphan*/ *,void const* const*,int) ; 

__attribute__((used)) static void
serialize_change(svn_temp_serializer__context_t *context,
                 svn_fs_x__change_t * const *change_p)
{
  const svn_fs_x__change_t * change = *change_p;
  if (change == NULL)
    return;

  /* serialize the change struct itself */
  svn_temp_serializer__push(context,
                            (const void * const *)change_p,
                            sizeof(*change));

  /* serialize sub-structures */
  svn_temp_serializer__add_string(context, &change->path.data);
  svn_temp_serializer__add_string(context, &change->copyfrom_path);

  /* return to the caller's nesting level */
  svn_temp_serializer__pop(context);
}