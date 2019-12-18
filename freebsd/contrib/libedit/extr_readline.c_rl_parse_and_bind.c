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
typedef  int /*<<< orphan*/  Tokenizer ;

/* Variables and functions */
 int /*<<< orphan*/  e ; 
 int el_parse (int /*<<< orphan*/ ,int,char const**) ; 
 int /*<<< orphan*/  tok_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tok_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tok_str (int /*<<< orphan*/ *,char const*,int*,char const***) ; 

int
rl_parse_and_bind(const char *line)
{
	const char **argv;
	int argc;
	Tokenizer *tok;

	tok = tok_init(NULL);
	tok_str(tok, line, &argc, &argv);
	argc = el_parse(e, argc, argv);
	tok_end(tok);
	return argc ? 1 : 0;
}