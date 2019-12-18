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
struct TYPE_7__ {int token_type; } ;
struct TYPE_6__ {TYPE_2__ token; } ;
typedef  TYPE_1__ parser_t ;

/* Variables and functions */
#define  TOKEN_TYPE_EOI 128 
 int /*<<< orphan*/  not_reached () ; 
 scalar_t__ parser_parse_value (TYPE_1__*) ; 
 scalar_t__ parser_tokenize (TYPE_1__*) ; 
 int /*<<< orphan*/  token_error (TYPE_2__*) ; 

__attribute__((used)) static bool
parser_parse(parser_t *parser) {
	if (parser_tokenize(parser)) {
		goto label_error;
	}
	if (parser_parse_value(parser)) {
		goto label_error;
	}

	if (parser_tokenize(parser)) {
		goto label_error;
	}
	switch (parser->token.token_type) {
	case TOKEN_TYPE_EOI:
		return false;
	default:
		goto label_error;
	}
	not_reached();

label_error:
	token_error(&parser->token);
	return true;
}