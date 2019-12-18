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
struct val_anchors {int dummy; } ;
struct trust_anchor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_CLASS_IN ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_DS ; 
 struct trust_anchor* anchor_store_new_key (struct val_anchors*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char const*) ; 
 int /*<<< orphan*/ * sldns_str2wire_dname (char const*,size_t*) ; 

__attribute__((used)) static struct trust_anchor*
anchor_insert_insecure(struct val_anchors* anchors, const char* str)
{
	struct trust_anchor* ta;
	size_t dname_len = 0;
	uint8_t* nm = sldns_str2wire_dname(str, &dname_len);
	if(!nm) {
		log_err("parse error in domain name '%s'", str);
		return NULL;
	}
	ta = anchor_store_new_key(anchors, nm, LDNS_RR_TYPE_DS,
		LDNS_RR_CLASS_IN, NULL, 0);
	free(nm);
	return ta;
}