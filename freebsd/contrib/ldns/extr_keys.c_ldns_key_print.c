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
typedef  int /*<<< orphan*/  ldns_key ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_FREE (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 char* ldns_key2str (int /*<<< orphan*/  const*) ; 

void
ldns_key_print(FILE *output, const ldns_key *k)
{
	char *str = ldns_key2str(k);
	if (str) {
                fprintf(output, "%s", str);
        } else {
                fprintf(output, "Unable to convert private key to string\n");
        }
        LDNS_FREE(str);
}