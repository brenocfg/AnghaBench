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
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_INT_NE (int,int) ; 
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshkey_load_file (int,struct sshbuf*) ; 
 int /*<<< orphan*/  test_data_file (char const*) ; 

struct sshbuf *
load_file(const char *name)
{
	int fd;
	struct sshbuf *ret;

	ASSERT_PTR_NE(ret = sshbuf_new(), NULL);
	ASSERT_INT_NE(fd = open(test_data_file(name), O_RDONLY), -1);
	ASSERT_INT_EQ(sshkey_load_file(fd, ret), 0);
	close(fd);
	return ret;
}