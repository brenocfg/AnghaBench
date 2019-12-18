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
 int /*<<< orphan*/  clean_gi (int,char**) ; 
 int cln_testonly ; 

void
tclean_gi(int argc, char *argv[])
{

	/* only difference between 'clean' and 'tclean' is one value */
	/* (...and the fact that 'clean' is priv and 'tclean' is not) */
	clean_gi(argc, argv);
	cln_testonly = 1;

	return;
}