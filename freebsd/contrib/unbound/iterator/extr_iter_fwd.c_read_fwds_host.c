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
typedef  int /*<<< orphan*/  uint8_t ;
struct delegpt {int dummy; } ;
struct config_stub {int /*<<< orphan*/  name; struct config_strlist* hosts; } ;
struct config_strlist {int /*<<< orphan*/  str; struct config_strlist* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  delegpt_add_ns_mlc (struct delegpt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int 
read_fwds_host(struct config_stub* s, struct delegpt* dp)
{
	struct config_strlist* p;
	uint8_t* dname;
	size_t dname_len;
	for(p = s->hosts; p; p = p->next) {
		log_assert(p->str);
		dname = sldns_str2wire_dname(p->str, &dname_len);
		if(!dname) {
			log_err("cannot parse forward %s server name: '%s'", 
				s->name, p->str);
			return 0;
		}
		if(!delegpt_add_ns_mlc(dp, dname, 0)) {
			free(dname);
			log_err("out of memory");
			return 0;
		}
		free(dname);
	}
	return 1;
}