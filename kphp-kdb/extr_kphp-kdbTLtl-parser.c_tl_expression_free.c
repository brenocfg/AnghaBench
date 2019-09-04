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
struct tl_expression {int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; int /*<<< orphan*/  right_name; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  cstr_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tl_list_token_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (struct tl_expression*,int) ; 

__attribute__((used)) static void tl_expression_free (struct tl_expression *E) {
  cstr_free (&E->text);
  cstr_free (&E->right_name);
  tl_list_token_free (E->left); E->left = NULL;
  tl_list_token_free (E->right); E->right = NULL;
  zfree (E, sizeof (*E));
}