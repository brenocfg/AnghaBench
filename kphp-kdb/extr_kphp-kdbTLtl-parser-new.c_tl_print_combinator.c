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
struct tl_constructor {char* real_id; char* id; int name; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf ; 
 char* buf_pos ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int output_expressions ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_buf_add_string (char*,int) ; 
 int /*<<< orphan*/  tl_buf_add_string_nospace (char*,int) ; 
 int /*<<< orphan*/  tl_buf_add_tree (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tl_buf_reset () ; 

int tl_print_combinator (struct tl_constructor *c) {
  tl_buf_reset ();
  tl_buf_add_string_nospace (c->real_id ? c->real_id : c->id, -1);
  static char _buf[10];
  sprintf (_buf, "#%08x", c->name);
  tl_buf_add_string_nospace (_buf, -1);
  tl_buf_add_tree (c->left, 1);
  tl_buf_add_string ("=", -1);
  tl_buf_add_tree (c->right, 1);
  if (output_expressions >= 1) {
    fprintf (stderr, "%.*s\n", buf_pos, buf);
  }
/*  if (!c->name) {
    c->name = compute_crc32 (buf, buf_pos);
  }*/
  return c->name;
}