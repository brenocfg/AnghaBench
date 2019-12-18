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
struct jv_parser {int /*<<< orphan*/  dtoa; int /*<<< orphan*/  tokenbuf; int /*<<< orphan*/  stack; int /*<<< orphan*/  output; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_mem_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jvp_dtoa_context_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parser_reset (struct jv_parser*) ; 

__attribute__((used)) static void parser_free(struct jv_parser* p) {
  parser_reset(p);
  jv_free(p->path);
  jv_free(p->output);
  jv_mem_free(p->stack);
  jv_mem_free(p->tokenbuf);
  jvp_dtoa_context_free(&p->dtoa);
}