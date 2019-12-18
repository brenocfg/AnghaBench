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
struct tl_constructor {int name; int /*<<< orphan*/  right; int /*<<< orphan*/  left; scalar_t__ id; scalar_t__ real_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct tl_constructor*) ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  buf_pos ; 
 int compute_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tl_buf_add_string (char*,int) ; 
 int /*<<< orphan*/  tl_buf_add_string_nospace (scalar_t__,int) ; 
 int /*<<< orphan*/  tl_buf_add_tree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tl_buf_reset () ; 

int tl_count_combinator_name (struct tl_constructor *c) {
  assert (c);
  tl_buf_reset ();
  tl_buf_add_string_nospace (c->real_id ? c->real_id : c->id, -1);
  tl_buf_add_tree (c->left, 1);
  tl_buf_add_string ("=", -1);
  tl_buf_add_tree (c->right, 1);
  //fprintf (stderr, "%.*s\n", buf_pos, buf);
  if (!c->name) {
    c->name = compute_crc32 (buf, buf_pos);
  }
  return c->name;
}