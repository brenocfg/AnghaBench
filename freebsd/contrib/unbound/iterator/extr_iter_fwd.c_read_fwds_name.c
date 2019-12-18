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
struct config_stub {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct delegpt* delegpt_create_mlc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static struct delegpt* 
read_fwds_name(struct config_stub* s)
{
	struct delegpt* dp;
	uint8_t* dname;
	size_t dname_len;
	if(!s->name) {
		log_err("forward zone without a name (use name \".\" to forward everything)");
		return NULL;
	}
	dname = sldns_str2wire_dname(s->name, &dname_len);
	if(!dname) {
		log_err("cannot parse forward zone name %s", s->name);
		return NULL;
	}
	if(!(dp=delegpt_create_mlc(dname))) {
		free(dname);
		log_err("out of memory");
		return NULL;
	}
	free(dname);
	return dp;
}