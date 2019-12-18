#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void svn_fs_id_t ;
struct TYPE_3__ {TYPE_2__* fsap_data; int /*<<< orphan*/ * vtable; } ;
struct TYPE_4__ {TYPE_1__ generic_id; } ;
typedef  TYPE_2__ fs_fs__id_t ;

/* Variables and functions */
 int /*<<< orphan*/  id_vtable ; 
 int /*<<< orphan*/  svn_temp_deserializer__resolve (void*,void**) ; 

void
svn_fs_fs__id_deserialize(void *buffer, svn_fs_id_t **in_out)
{
  fs_fs__id_t *id;

  /* The id maybe all what is in the whole buffer.
   * Don't try to fixup the pointer in that case*/
  if (*in_out != buffer)
    svn_temp_deserializer__resolve(buffer, (void**)in_out);

  id = (fs_fs__id_t *)*in_out;

  /* no id, no sub-structure fixup necessary */
  if (id == NULL)
    return;

  /* the stored vtable is bogus at best -> set the right one */
  id->generic_id.vtable = &id_vtable;
  id->generic_id.fsap_data = id;
}