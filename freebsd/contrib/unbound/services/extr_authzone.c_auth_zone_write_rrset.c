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
struct auth_zone {int /*<<< orphan*/  dclass; } ;
struct auth_rrset {TYPE_1__* data; int /*<<< orphan*/  type; } ;
struct auth_data {int /*<<< orphan*/  namelen; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {size_t count; size_t rrsig_count; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LDNS_RR_BUF_SIZE ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  auth_rr_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,size_t,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  write_out (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
auth_zone_write_rrset(struct auth_zone* z, struct auth_data* node,
	struct auth_rrset* r, FILE* out)
{
	size_t i, count = r->data->count + r->data->rrsig_count;
	char buf[LDNS_RR_BUF_SIZE];
	for(i=0; i<count; i++) {
		if(!auth_rr_to_string(node->name, node->namelen, r->type,
			z->dclass, r->data, i, buf, sizeof(buf))) {
			verbose(VERB_ALGO, "failed to rr2str rr %d", (int)i);
			continue;
		}
		if(!write_out(out, buf, strlen(buf)))
			return 0;
	}
	return 1;
}