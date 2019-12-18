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
struct krb5_krbhst_info {scalar_t__ proto; scalar_t__ port; struct krb5_krbhst_info* next; int /*<<< orphan*/  hostname; } ;
struct krb5_krbhst_data {struct krb5_krbhst_info** end; struct krb5_krbhst_info* hosts; } ;

/* Variables and functions */
 int /*<<< orphan*/  _krb5_free_krbhst_info (struct krb5_krbhst_info*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
append_host_hostinfo(struct krb5_krbhst_data *kd, struct krb5_krbhst_info *host)
{
    struct krb5_krbhst_info *h;

    for(h = kd->hosts; h; h = h->next)
	if(h->proto == host->proto &&
	   h->port == host->port &&
	   strcmp(h->hostname, host->hostname) == 0) {
	    _krb5_free_krbhst_info(host);
	    return;
	}
    *kd->end = host;
    kd->end = &host->next;
}