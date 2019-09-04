#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yyscan_t ;
struct locfile {int dummy; } ;
struct lexer_param {int /*<<< orphan*/  lexer; } ;
typedef  int /*<<< orphan*/  jv ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_4__ {int /*<<< orphan*/  literal; } ;
typedef  TYPE_1__ YYSTYPE ;
typedef  int /*<<< orphan*/  YYLTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ JV_KIND_STRING ; 
 int LITERAL ; 
 int QQSTRING_TEXT ; 
 int jq_yylex (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_copy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_invalid_get_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_null () ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 

int yylex(YYSTYPE* yylval, YYLTYPE* yylloc, block* answer, int* errors,
          struct locfile* locations, struct lexer_param* lexer_param_ptr) {
  yyscan_t lexer = lexer_param_ptr->lexer;
  int tok = jq_yylex(yylval, yylloc, lexer);
  if ((tok == LITERAL || tok == QQSTRING_TEXT) && !jv_is_valid(yylval->literal)) {
    jv msg = jv_invalid_get_msg(jv_copy(yylval->literal));
    if (jv_get_kind(msg) == JV_KIND_STRING) {
      FAIL(*yylloc, jv_string_value(msg));
    } else {
      FAIL(*yylloc, "Invalid literal");
    }
    jv_free(msg);
    jv_free(yylval->literal);
    yylval->literal = jv_null();
  }
  return tok;
}