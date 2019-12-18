#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  token_t ;
struct TYPE_3__ {int /*<<< orphan*/  machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_UNAVAILABLE ; 
 int /*<<< orphan*/ * au_to_subject32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  inet_addr (char*) ; 
 int /*<<< orphan*/  subject32_auid ; 
 int /*<<< orphan*/  subject32_egid ; 
 int /*<<< orphan*/  subject32_euid ; 
 int /*<<< orphan*/  subject32_pid ; 
 int /*<<< orphan*/  subject32_rgid ; 
 int /*<<< orphan*/  subject32_ruid ; 
 int /*<<< orphan*/  subject32_sid ; 
 TYPE_1__ subject32_tid ; 
 int /*<<< orphan*/  write_token (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
generate_subject32_token(const char *directory, const char *token_filename)
{
	token_t *subject32_token;

	subject32_tid.machine = inet_addr("127.0.0.1");

	subject32_token = au_to_subject32(subject32_auid, subject32_euid,
	    subject32_egid, subject32_ruid, subject32_rgid, subject32_pid,
	    subject32_sid, &subject32_tid);
	if (subject32_token == NULL)
		err(EX_UNAVAILABLE, "au_to_subject32");
	write_token(directory, token_filename, subject32_token);
}