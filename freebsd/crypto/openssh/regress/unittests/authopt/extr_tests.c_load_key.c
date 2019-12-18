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
struct sshkey {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshkey*,int /*<<< orphan*/ *) ; 
 int sshkey_load_public (int /*<<< orphan*/ ,struct sshkey**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_data_file (char const*) ; 

__attribute__((used)) static struct sshkey *
load_key(const char *name)
{
	struct sshkey *ret;
	int r;

	r = sshkey_load_public(test_data_file(name), &ret, NULL);
	ASSERT_INT_EQ(r, 0);
	ASSERT_PTR_NE(ret, NULL);
	return ret;
}