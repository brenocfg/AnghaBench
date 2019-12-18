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
struct auth_zone {int /*<<< orphan*/ * zonefile; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

int
auth_zone_set_zonefile(struct auth_zone* z, char* zonefile)
{
	if(z->zonefile) free(z->zonefile);
	if(zonefile == NULL) {
		z->zonefile = NULL;
	} else {
		z->zonefile = strdup(zonefile);
		if(!z->zonefile) {
			log_err("malloc failure");
			return 0;
		}
	}
	return 1;
}