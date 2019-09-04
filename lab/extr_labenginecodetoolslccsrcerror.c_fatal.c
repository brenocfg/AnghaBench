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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int errcnt ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprint (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  print (char*) ; 
 int /*<<< orphan*/  stderr ; 

int fatal(const char *name, const char *fmt, int n) {
	print("\n");
	errcnt = -1;
	error("compiler error in %s--", name);
	fprint(stderr, fmt, n);
	exit(EXIT_FAILURE);
	return 0;
}