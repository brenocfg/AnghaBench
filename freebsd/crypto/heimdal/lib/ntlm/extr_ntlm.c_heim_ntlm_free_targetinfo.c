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
struct ntlm_targetinfo {int /*<<< orphan*/  dnstreename; int /*<<< orphan*/  dnsservername; int /*<<< orphan*/  dnsdomainname; int /*<<< orphan*/  domainname; int /*<<< orphan*/  servername; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ntlm_targetinfo*,int /*<<< orphan*/ ,int) ; 

void
heim_ntlm_free_targetinfo(struct ntlm_targetinfo *ti)
{
    free(ti->servername);
    free(ti->domainname);
    free(ti->dnsdomainname);
    free(ti->dnsservername);
    free(ti->dnstreename);
    memset(ti, 0, sizeof(*ti));
}