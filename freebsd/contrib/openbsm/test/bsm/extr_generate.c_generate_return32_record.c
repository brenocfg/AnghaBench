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
 int /*<<< orphan*/  AUE_NULL ; 
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/  au_errno_to_bsm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * au_to_return32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  return32_ret ; 
 int /*<<< orphan*/  return32_status ; 
 int /*<<< orphan*/  write_record (char const*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
generate_return32_record(const char *directory, const char *record_filename)
{
	token_t *return32_token;

	return32_token = au_to_return32(au_errno_to_bsm(return32_status),
	    return32_ret);
	if (return32_token == NULL)
		err(EX_UNAVAILABLE, "au_to_return32");
	write_record(directory, record_filename, return32_token, AUE_NULL);
}