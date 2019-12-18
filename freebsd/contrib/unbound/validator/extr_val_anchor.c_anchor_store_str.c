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
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_WIREPARSE_OFFSET (int) ; 
 struct trust_anchor* anchor_store_new_rr (struct val_anchors*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/ * sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 size_t sldns_buffer_capacity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_get_errorstr_parse (int) ; 
 int sldns_str2wire_rr_buf (char const*,int /*<<< orphan*/ *,size_t*,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct trust_anchor*
anchor_store_str(struct val_anchors* anchors, sldns_buffer* buffer,
	const char* str)
{
	struct trust_anchor* ta;
	uint8_t* rr = sldns_buffer_begin(buffer);
	size_t len = sldns_buffer_capacity(buffer), dname_len = 0;
	int status = sldns_str2wire_rr_buf(str, rr, &len, &dname_len,
		0, NULL, 0, NULL, 0);
	if(status != 0) {
		log_err("error parsing trust anchor %s: at %d: %s", 
			str, LDNS_WIREPARSE_OFFSET(status),
			sldns_get_errorstr_parse(status));
		return NULL;
	}
	if(!(ta=anchor_store_new_rr(anchors, rr, len, dname_len))) {
		log_err("out of memory");
		return NULL;
	}
	return ta;
}