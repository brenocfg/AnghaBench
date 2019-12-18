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
struct tree_payload {scalar_t__ text; } ;
struct TYPE_2__ {scalar_t__ N; } ;

/* Variables and functions */
 struct tree_payload* LPAYLOAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NODE_RPOS (int /*<<< orphan*/ *) ; 
 TYPE_1__ OTree ; 
 int get_text_len (scalar_t__) ; 
 int /*<<< orphan*/  metafile_get_text (scalar_t__,int*) ; 
 int new_text_cur_offset ; 
 int /*<<< orphan*/  writeout_int (int) ; 

__attribute__((used)) static int tree_write_text_offset (tree_ext_small_t *T) {
  writeout_int (new_text_cur_offset);
  struct tree_payload *P = LPAYLOAD (T);
  int text_len;
  if (P->text) {
    text_len = get_text_len (P->text);
  } else {
    metafile_get_text (OTree.N - NODE_RPOS (T), &text_len);
  }
  new_text_cur_offset += text_len;
  return 0;
}