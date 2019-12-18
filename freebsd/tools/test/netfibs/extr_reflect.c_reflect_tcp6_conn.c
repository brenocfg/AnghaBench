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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EX_OSERR ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 
 int reflect_conn (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reflect_tcp6_conn(int as)
{
	char buf[1500];
	ssize_t l;
	int error, s;

	s = accept(as, NULL, NULL);
	if (s == -1)
		err(EX_OSERR, "accept()");

	l = read(s, buf, sizeof(buf));
	error = reflect_conn(s, buf, sizeof(buf), l, NULL, 0);
	close(s);

	return (error);
}