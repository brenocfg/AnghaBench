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
 int LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int sldns_get_rr_class_by_name (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
massage_class(const char* c)
{
	if(c) {
		int r = sldns_get_rr_class_by_name(c);
		if(r == 0 && strcasecmp(c, "CLASS0") != 0 && 
			strcmp(c, "") != 0) {
			fprintf(stderr, "error unknown class %s\n", c);
			exit(1);
		}
		return r;
	}
	return LDNS_RR_CLASS_IN;
}