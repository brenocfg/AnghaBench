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

/* Variables and functions */
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_FLAG_NO_BUFFERING ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  maybe_redirect_std_handle (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void maybe_redirect_std_handles(void)
{
	maybe_redirect_std_handle(L"GIT_REDIRECT_STDIN", STD_INPUT_HANDLE, 0,
				  GENERIC_READ, FILE_ATTRIBUTE_NORMAL);
	maybe_redirect_std_handle(L"GIT_REDIRECT_STDOUT", STD_OUTPUT_HANDLE, 1,
				  GENERIC_WRITE, FILE_ATTRIBUTE_NORMAL);
	maybe_redirect_std_handle(L"GIT_REDIRECT_STDERR", STD_ERROR_HANDLE, 2,
				  GENERIC_WRITE, FILE_FLAG_NO_BUFFERING);
}