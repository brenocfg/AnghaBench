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
struct iter_forwards {int dummy; } ;
struct config_stub {int /*<<< orphan*/  name; struct config_stub* next; } ;
struct config_file {struct config_stub* stubs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwd_add_stub_hole (struct iter_forwards*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
make_stub_holes(struct iter_forwards* fwd, struct config_file* cfg)
{
	struct config_stub* s;
	uint8_t* dname;
	size_t dname_len;
	for(s = cfg->stubs; s; s = s->next) {
		if(!s->name) continue;
		dname = sldns_str2wire_dname(s->name, &dname_len);
		if(!dname) {
			log_err("cannot parse stub name '%s'", s->name);
			return 0;
		}
		if(!fwd_add_stub_hole(fwd, LDNS_RR_CLASS_IN, dname)) {
			free(dname);
			log_err("out of memory");
			return 0;
		}
		free(dname);
	}
	return 1;
}