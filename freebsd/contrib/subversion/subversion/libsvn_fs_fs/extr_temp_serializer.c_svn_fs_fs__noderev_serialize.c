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
struct TYPE_3__ {int /*<<< orphan*/  created_path; int /*<<< orphan*/  copyroot_path; int /*<<< orphan*/  copyfrom_path; int /*<<< orphan*/  data_rep; int /*<<< orphan*/  prop_rep; int /*<<< orphan*/  predecessor_id; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ node_revision_t ;

/* Variables and functions */
 int /*<<< orphan*/  serialize_representation (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_fs__id_serialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_temp_serializer__push (int /*<<< orphan*/ *,void const* const*,int) ; 

void
svn_fs_fs__noderev_serialize(svn_temp_serializer__context_t *context,
                             node_revision_t * const *noderev_p)
{
  const node_revision_t *noderev = *noderev_p;
  if (noderev == NULL)
    return;

  /* serialize the representation struct itself */
  svn_temp_serializer__push(context,
                            (const void * const *)noderev_p,
                            sizeof(*noderev));

  /* serialize sub-structures */
  svn_fs_fs__id_serialize(context, &noderev->id);
  svn_fs_fs__id_serialize(context, &noderev->predecessor_id);
  serialize_representation(context, &noderev->prop_rep);
  serialize_representation(context, &noderev->data_rep);

  svn_temp_serializer__add_string(context, &noderev->copyfrom_path);
  svn_temp_serializer__add_string(context, &noderev->copyroot_path);
  svn_temp_serializer__add_string(context, &noderev->created_path);

  /* return to the caller's nesting level */
  svn_temp_serializer__pop(context);
}