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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* ldns_rdf2str (int /*<<< orphan*/  const*) ; 

void
ldns_rdf_print(FILE *output, const ldns_rdf *rdf)
{
	char *str = ldns_rdf2str(rdf);
	if (str) {
		fprintf(output, "%s", str);
	} else {
		fprintf(output, ";Unable to convert rdf to string\n");
	}
	LDNS_FREE(str);
}