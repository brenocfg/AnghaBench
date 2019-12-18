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
 int /*<<< orphan*/ * au_to_opaque (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  opaque_token_bytes ; 
 int /*<<< orphan*/  opaque_token_data ; 
 int /*<<< orphan*/  write_token (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
generate_opaque_token(const char *directory, const char *token_filename)
{
	token_t *opaque_token;

	opaque_token = au_to_opaque(opaque_token_data, opaque_token_bytes);
	if (opaque_token == NULL)
		err(EX_UNAVAILABLE, "au_to_opaque");
	write_token(directory, token_filename, opaque_token);
}