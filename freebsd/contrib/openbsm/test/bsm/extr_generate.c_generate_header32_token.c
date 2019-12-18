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
 int /*<<< orphan*/ * au_to_header32_tm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  header32_e_mod ; 
 int /*<<< orphan*/  header32_e_type ; 
 int /*<<< orphan*/  header32_tm ; 
 int /*<<< orphan*/  header32_token_len ; 
 int /*<<< orphan*/  write_token (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
generate_header32_token(const char *directory, const char *token_filename)
{
	token_t *header32_token;

	header32_token = au_to_header32_tm(header32_token_len,
	    header32_e_type, header32_e_mod, header32_tm);
	if (header32_token == NULL)
		err(EX_UNAVAILABLE, "au_to_header32");
	write_token(directory, token_filename, header32_token);
}