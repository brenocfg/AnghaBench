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
typedef  int /*<<< orphan*/  ldns_rr_list ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* LDNS_RESOLV_HOSTS ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/ * ldns_get_rr_list_hosts_frm_fp (int /*<<< orphan*/ *) ; 

ldns_rr_list *
ldns_get_rr_list_hosts_frm_file(char *filename)
{
	ldns_rr_list *names;
	FILE *fp;

	if (!filename) {
                fp = fopen(LDNS_RESOLV_HOSTS, "r");
        
        } else {
                fp = fopen(filename, "r");
        }
        if (!fp) {
                return NULL;
        }

	names = ldns_get_rr_list_hosts_frm_fp(fp);
	fclose(fp);
	return names;
}