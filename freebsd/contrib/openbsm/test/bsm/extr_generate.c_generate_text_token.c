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
typedef  int /*<<< orphan*/  token_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/ * au_to_text (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  text_token_text ; 
 int /*<<< orphan*/  write_token (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
generate_text_token(const char *directory, const char *token_filename)
{
	token_t *text_token;

	text_token = au_to_text(text_token_text);
	if (text_token == NULL)
		err(EX_UNAVAILABLE, "au_to_text");
	write_token(directory, token_filename, text_token);
}