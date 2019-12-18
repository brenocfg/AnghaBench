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
struct tl_expression {scalar_t__ type; unsigned int magic; int /*<<< orphan*/  text; } ;
struct tl_compiler {int dummy; } ;

/* Variables and functions */
 unsigned int compute_crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int tl_failf (struct tl_compiler*,char*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ tlet_simple ; 

int tl_expression_compute_magic (struct tl_compiler *C, struct tl_expression *E) {
  if (E->type != tlet_simple) {
    return 0;
  }
  unsigned m = compute_crc32 (E->text, strlen (E->text));
  if (E->magic && E->magic != m) {
     return tl_failf (C, "tl_expression_compute_magic: magic in schema (0x%x) isn't equal to computed magic (0x%x), expr: %s", E->magic, m, E->text);
  }
  E->magic = m;
  return 0;
}