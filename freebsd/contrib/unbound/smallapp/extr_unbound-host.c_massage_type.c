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
 int LDNS_RR_TYPE_A ; 
 int LDNS_RR_TYPE_PTR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int sldns_get_rr_type_by_name (char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
massage_type(const char* t, int reverse, int* multi)
{
	if(t) {
		int r = sldns_get_rr_type_by_name(t);
		if(r == 0 && strcasecmp(t, "TYPE0") != 0 && 
			strcmp(t, "") != 0) {
			fprintf(stderr, "error unknown type %s\n", t);
			exit(1);
		}
		return r;
	}
	if(!t && reverse)
		return LDNS_RR_TYPE_PTR;
	*multi = 1;
	return LDNS_RR_TYPE_A;
}