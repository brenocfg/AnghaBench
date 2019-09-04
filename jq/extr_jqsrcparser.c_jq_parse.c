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
struct locfile {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
struct lexer_param {int /*<<< orphan*/  lexer; } ;
typedef  int /*<<< orphan*/  block ;
typedef  int /*<<< orphan*/  YY_BUFFER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  block_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_noop () ; 
 int /*<<< orphan*/  jq_yy_delete_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jq_yy_scan_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jq_yylex_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jq_yylex_init_extra (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yyparse (int /*<<< orphan*/ *,int*,struct locfile*,struct lexer_param*) ; 

int jq_parse(struct locfile* locations, block* answer) {
  struct lexer_param scanner;
  YY_BUFFER_STATE buf;
  jq_yylex_init_extra(0, &scanner.lexer);
  buf = jq_yy_scan_bytes(locations->data, locations->length, scanner.lexer);
  int errors = 0;
  *answer = gen_noop();
  yyparse(answer, &errors, locations, &scanner);
  jq_yy_delete_buffer(buf, scanner.lexer);
  jq_yylex_destroy(scanner.lexer);
  if (errors > 0) {
    block_free(*answer);
    *answer = gen_noop();
  }
  return errors;
}