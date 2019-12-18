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
 int /*<<< orphan*/  arg32_token_n ; 
 int /*<<< orphan*/  arg32_token_text ; 
 int /*<<< orphan*/  arg32_token_v ; 
 int /*<<< orphan*/ * au_to_arg32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  write_token (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
generate_arg32_token(const char *directory, const char *token_filename)
{
	token_t *arg32_token;

	arg32_token = au_to_arg32(arg32_token_n, arg32_token_text,
	    arg32_token_v);
	if (arg32_token == NULL)
		err(EX_UNAVAILABLE, "au_to_arg32");
	write_token(directory, token_filename, arg32_token);
}