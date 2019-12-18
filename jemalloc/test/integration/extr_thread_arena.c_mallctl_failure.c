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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFERROR_BUF ; 
 int /*<<< orphan*/  buferror (int,char*,int) ; 
 int /*<<< orphan*/  test_fail (char*,char*) ; 

__attribute__((used)) static void
mallctl_failure(int err) {
	char buf[BUFERROR_BUF];

	buferror(err, buf, sizeof(buf));
	test_fail("Error in mallctl(): %s", buf);
}