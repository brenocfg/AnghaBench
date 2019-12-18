#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree_ext_small_t ;
struct tree_payload {scalar_t__ text; scalar_t__ date; scalar_t__ value; scalar_t__ flags; } ;
struct TYPE_2__ {scalar_t__ N; } ;

/* Variables and functions */
 int /*<<< orphan*/  LF_BIGFLAGS ; 
 int /*<<< orphan*/  LF_HAVE_DATES ; 
 int /*<<< orphan*/  LF_HAVE_TEXTS ; 
 int /*<<< orphan*/  LF_HAVE_VALUES ; 
 struct tree_payload* LPAYLOAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NODE_RPOS (int /*<<< orphan*/ *) ; 
 TYPE_1__ OTree ; 
 int /*<<< orphan*/  assert (int) ; 
 int get_text_len (scalar_t__) ; 
 int /*<<< orphan*/  metafile_get_text (scalar_t__,int*) ; 
 int /*<<< orphan*/  new_flags ; 

__attribute__((used)) static int tree_build_flags (tree_ext_small_t *T) {
  struct tree_payload *P = LPAYLOAD (T);
  if ((unsigned)P->flags >= 256) {
    new_flags |= LF_BIGFLAGS;
  }

  if (P->value) {
    new_flags |= LF_HAVE_VALUES;
  }

  if (P->date) {
    new_flags |= LF_HAVE_DATES;
  }

  int text_len = -1;
  if (P->text) {
    text_len = get_text_len (P->text);
  } else {
    metafile_get_text (OTree.N - NODE_RPOS (T), &text_len);
  }
  assert (text_len >= 0);

  if (text_len) {
    new_flags |= LF_HAVE_TEXTS;
  }
  return 0;
}