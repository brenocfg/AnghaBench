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
typedef  int /*<<< orphan*/  svn_temp_serializer__context_t ;
typedef  int /*<<< orphan*/  svn_fs_id_t ;
typedef  int /*<<< orphan*/  fs_fs__id_t ;

/* Variables and functions */
 int /*<<< orphan*/  svn_temp_serializer__add_leaf (int /*<<< orphan*/ *,void const* const*,int) ; 

void
svn_fs_fs__id_serialize(svn_temp_serializer__context_t *context,
                        const svn_fs_id_t * const *in)
{
  const fs_fs__id_t *id = (const fs_fs__id_t *)*in;

  /* nothing to do for NULL ids */
  if (id == NULL)
    return;

  /* Serialize the id data struct itself.
   * Note that the structure behind IN is actually larger than a mere
   * svn_fs_id_t . */
  svn_temp_serializer__add_leaf(context,
                                (const void * const *)in,
                                sizeof(fs_fs__id_t));
}