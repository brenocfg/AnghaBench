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
struct signature_check {int dummy; } ;
struct commit {int dummy; } ;
typedef  int /*<<< orphan*/  signature_check ;

/* Variables and functions */
 int check_commit_signature (struct commit*,struct signature_check*) ; 
 int /*<<< orphan*/  memset (struct signature_check*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_signature_buffer (struct signature_check*,unsigned int) ; 
 int /*<<< orphan*/  signature_check_clear (struct signature_check*) ; 

__attribute__((used)) static int run_gpg_verify(struct commit *commit, unsigned flags)
{
	struct signature_check signature_check;
	int ret;

	memset(&signature_check, 0, sizeof(signature_check));

	ret = check_commit_signature(commit, &signature_check);
	print_signature_buffer(&signature_check, flags);

	signature_check_clear(&signature_check);
	return ret;
}