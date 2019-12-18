#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int token_type; } ;
struct TYPE_7__ {TYPE_1__ token; } ;
typedef  TYPE_2__ parser_t ;

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_TYPE_LBRACE ; 
#define  TOKEN_TYPE_RBRACE 129 
#define  TOKEN_TYPE_STRING 128 
 int /*<<< orphan*/  assert_d_eq (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  not_reached () ; 
 int parser_parse_pairs (TYPE_2__*) ; 
 scalar_t__ parser_tokenize (TYPE_2__*) ; 

__attribute__((used)) static bool
parser_parse_object(parser_t *parser) {
	assert_d_eq(parser->token.token_type, TOKEN_TYPE_LBRACE,
	    "Object should start with {");
	if (parser_tokenize(parser)) {
		return true;
	}
	switch (parser->token.token_type) {
	case TOKEN_TYPE_STRING:
		return parser_parse_pairs(parser);
	case TOKEN_TYPE_RBRACE:
		return false;
	default:
		return true;
	}
	not_reached();
}