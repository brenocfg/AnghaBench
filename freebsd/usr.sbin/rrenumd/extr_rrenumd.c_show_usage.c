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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
show_usage()
{
	fprintf(stderr, "usage: rrenumd [-c conf_file|-s] [-df"
#ifdef IPSEC
#ifdef IPSEC_POLICY_IPSEC
		"] [-P policy"
#else /* IPSEC_POLICY_IPSEC */
		"AE"
#endif /* IPSEC_POLICY_IPSEC */
#endif /* IPSEC */
		"]\n");
	exit(1);
}