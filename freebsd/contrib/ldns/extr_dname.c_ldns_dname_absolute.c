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
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (char*) ; 
 int ldns_dname_str_absolute (char*) ; 
 char* ldns_rdf2str (int /*<<< orphan*/  const*) ; 

bool
ldns_dname_absolute(const ldns_rdf *rdf)
{
	char *str = ldns_rdf2str(rdf);
	if (str) {
		bool r = ldns_dname_str_absolute(str);
		LDNS_FREE(str);
		return r;
	}
	return false;
}