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
typedef  int /*<<< orphan*/  git_time_t ;
typedef  int /*<<< orphan*/  git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int git_signature_new (int /*<<< orphan*/ **,char const*,char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int try_build_signature(const char *name, const char *email, git_time_t time, int offset)
{
	git_signature *sign;
	int error = 0;

	if ((error =  git_signature_new(&sign, name, email, time, offset)) < 0)
		return error;

	git_signature_free((git_signature *)sign);

	return error;
}