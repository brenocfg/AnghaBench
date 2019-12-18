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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  die (int,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_get_errorstr_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_str2rdf_dname (int /*<<< orphan*/ **,char const*) ; 

__attribute__((used)) static ldns_rdf*
safe_str2rdf_dname(const char *name) {
    ldns_rdf *dname;
    ldns_status status;

    if ((status = ldns_str2rdf_dname(&dname, name)) != LDNS_STATUS_OK) {
        die(1, "'%s' is not a legal name (%s)",
            name, ldns_get_errorstr_by_id(status));
    }
    return dname;
}