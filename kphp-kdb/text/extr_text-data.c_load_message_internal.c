#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_3__* mf; int /*<<< orphan*/  edit_text_tree; int /*<<< orphan*/  msg_tree; } ;
typedef  TYPE_4__ user_t ;
struct TYPE_17__ {int y; int flags; scalar_t__ edit_text; TYPE_2__* value; TYPE_1__* msg; } ;
typedef  TYPE_5__ tree_t ;
struct imessage {int flags; TYPE_7__* fmsg; scalar_t__ edit_text; TYPE_2__* value_actions; TYPE_1__* msg; scalar_t__ m_extra; } ;
struct file_user_list_entry {int user_last_local_id; int /*<<< orphan*/  user_data_size; } ;
struct TYPE_18__ {char* data; } ;
typedef  TYPE_6__ core_mf_t ;
struct TYPE_19__ {int flags; } ;
struct TYPE_15__ {int /*<<< orphan*/  len; } ;
struct TYPE_14__ {int flags; } ;
struct TYPE_13__ {int flags; } ;

/* Variables and functions */
#define  TF_MINUS 132 
#define  TF_PLUS 131 
#define  TF_REPLACED 130 
#define  TF_ZERO 129 
#define  TF_ZERO_PRIME 128 
 int /*<<< orphan*/  assert (int) ; 
 char* get_user_metafile (TYPE_4__*) ; 
 TYPE_6__* load_user_metafile (int) ; 
 TYPE_5__* tree_lookup (int /*<<< orphan*/ ,int) ; 
 TYPE_7__* user_metafile_message_lookup (char*,int /*<<< orphan*/ ,int,TYPE_4__*) ; 

int load_message_internal (struct imessage *M, user_t *U, struct file_user_list_entry *D, int user_id, int local_id, int force) {
  tree_t *T;
  char *metafile;

//  fprintf (stderr, "load_message(%d,%d):\n", user_id, local_id);

  /* U = get_user (user_id); */
  T = 0;
  M->msg = 0;
  M->fmsg = 0;
  M->m_extra = 0;
  M->flags = -1;
  M->value_actions = 0;
  M->edit_text = 0;

  if (U) {
    /* D = U->dir_entry; */
    T = tree_lookup (U->msg_tree, local_id);
    if (T) {
      switch (T->y & 7) {
      case TF_PLUS:
      case TF_REPLACED:
        M->msg = T->msg;
        M->flags = T->msg->flags;
        return 1;
      case TF_MINUS:
        return 0;
      case TF_ZERO:
        M->flags = T->flags;
        break;
      case TF_ZERO_PRIME:
        M->flags = T->value->flags;
        M->value_actions = T->value;
        break;
      default:
        assert (0);
      }
    }
    tree_t *X = tree_lookup (U->edit_text_tree, local_id);
    if (X) {
      M->edit_text = X->edit_text;
    }
  } else {
    /* D = lookup_user_directory (user_id); */
    T = 0;
  }
  if (!D || local_id > D->user_last_local_id) {
    assert (!T);
    return 0;
  }
  if (!U || !get_user_metafile (U)) {
    if (!force) {
      return -2;
    }
    core_mf_t *M = load_user_metafile (user_id);
    if (!M) {
      return -2;
    }
    metafile = M->data;
  } else {
    metafile = get_user_metafile (U);
    assert (U->mf && U->mf->len >= D->user_data_size);
  }
  /* now metafile points to user metafile, and we have to get M->fmsg from there */
  M->fmsg = user_metafile_message_lookup (metafile, D->user_data_size, local_id, U);
  assert (!T || M->fmsg);
  if (M->flags < 0 && M->fmsg) {
    M->flags = M->fmsg->flags & 0xffff;
  }
  return M->fmsg ? 1 : 0;
}