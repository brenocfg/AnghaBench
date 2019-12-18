#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int kind; } ;
typedef  TYPE_1__ token ;

/* Variables and functions */
#define  TOK_CHAR 132 
#define  TOK_HYPER 131 
#define  TOK_INT 130 
#define  TOK_LONG 129 
#define  TOK_SHORT 128 
 int /*<<< orphan*/  get_token (TYPE_1__*) ; 
 int /*<<< orphan*/  peek (TYPE_1__*) ; 
 int /*<<< orphan*/  peekscan (int,TYPE_1__*) ; 

__attribute__((used)) static void
unsigned_dec(const char **typep)
{
	token tok;

	peek(&tok);
	switch (tok.kind) {
	case TOK_CHAR:
		get_token(&tok);
		*typep = "u_char";
		break;
	case TOK_SHORT:
		get_token(&tok);
		*typep = "u_short";
		(void) peekscan(TOK_INT, &tok);
		break;
	case TOK_LONG:
		get_token(&tok);
		*typep = "u_long";
		(void) peekscan(TOK_INT, &tok);
		break;
	case TOK_HYPER:
		get_token(&tok);
		*typep = "u_int64_t";

		(void) peekscan(TOK_INT, &tok);
		break;
	case TOK_INT:
		get_token(&tok);
		*typep = "u_int";
		break;
	default:
		*typep = "u_int";
		break;
	}
}