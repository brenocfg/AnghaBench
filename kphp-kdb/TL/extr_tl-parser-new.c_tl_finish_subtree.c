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
struct tl_combinator_tree {scalar_t__ type; scalar_t__ type_len; int /*<<< orphan*/  act; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_ACT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TL_ERROR (char*) ; 
 int /*<<< orphan*/  TL_TYPE (scalar_t__) ; 
 int _tl_finish_subtree (struct tl_combinator_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (struct tl_combinator_tree*) ; 
 scalar_t__ type_type ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int tl_finish_subtree (struct tl_combinator_tree *R) {
  assert (R);
  vkprintf (2, "finish_subtree. Type = %s. Act = %s\n", TL_TYPE (R->type), TL_ACT (R->act));
  if (R->type != type_type) {
    return 1;
  }
  if (R->type_len >= 0) {
    if (R->type_len > 0) {
      TL_ERROR ("Not enough params\n");
      return 0;
    }
    return 1;
  }
  return _tl_finish_subtree (R, 0, 0);
}