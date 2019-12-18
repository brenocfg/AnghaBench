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
 scalar_t__ isip4 (char const*,char**) ; 
 scalar_t__ isip6 (char const*,char**) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 

__attribute__((used)) static char*
massage_qname(const char* nm, int* reverse)
{
	/* recognise IP4 and IP6, create reverse addresses if needed */
	char* res;
	if(isip4(nm, &res)) {
		*reverse = 1;
	} else if(isip6(nm, &res)) {
		*reverse = 1;
	} else {
		res = strdup(nm);
	}
	if(!res) {
		fprintf(stderr, "error: out of memory\n");
		exit(1);
	}
	return res;
}