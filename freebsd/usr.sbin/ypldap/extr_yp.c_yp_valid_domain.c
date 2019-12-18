#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ypresp_val {int /*<<< orphan*/  stat; } ;
struct TYPE_2__ {int /*<<< orphan*/  sc_domainname; } ;

/* Variables and functions */
 int /*<<< orphan*/  YP_NODOM ; 
 TYPE_1__* env ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

int
yp_valid_domain(char *domain, struct ypresp_val *res)
{
	if (domain == NULL) {
		log_debug("NULL domain !");
		return (-1);
	}
	if (strcmp(domain, env->sc_domainname) != 0) {
		res->stat = YP_NODOM;
		return (-1);
	}
	return (0);
}