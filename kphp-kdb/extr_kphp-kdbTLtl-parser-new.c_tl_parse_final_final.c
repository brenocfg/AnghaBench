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
struct tree {scalar_t__ type; int nc; TYPE_1__** c; } ;
struct tl_type {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  text; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  TL_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TL_FAIL ; 
 int /*<<< orphan*/  assert (int) ; 
 struct tl_type* tl_get_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ type_final_final ; 

int tl_parse_final_final (struct tree *T) {
  assert (T->type == type_final_final);
  assert (T->nc == 1);
  struct tl_type *R;
  if ((R = tl_get_type (T->c[0]->text, T->c[0]->len))) {
    R->flags |= 1;
    return 1;
  } else {
    TL_ERROR ("Final statement for type `%.*s` before declaration\n", T->c[0]->len, T->c[0]->text);
    TL_FAIL;
  }
}