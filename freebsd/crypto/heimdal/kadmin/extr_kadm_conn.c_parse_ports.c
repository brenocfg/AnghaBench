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
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  add_kadm_port (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_standard_ports (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strsep_copy (char const**,char*,char*,int) ; 

void
parse_ports(krb5_context contextp, const char *str)
{
    char p[128];

    while(strsep_copy(&str, " \t", p, sizeof(p)) != -1) {
	if(strcmp(p, "+") == 0)
	    add_standard_ports(contextp);
	else
	    add_kadm_port(contextp, p, 0);
    }
}