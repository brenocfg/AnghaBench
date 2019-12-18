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
 int /*<<< orphan*/  VERB_QUERY ; 
 struct trust_anchor* anchor_store_new_key (struct val_anchors*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ sldns_wirerr_get_rdatalen (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_wirerr_get_rdatawl (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_wirerr_get_type (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static struct trust_anchor*
anchor_store_new_rr(struct val_anchors* anchors, uint8_t* rr, size_t rl,
	size_t dl)
{
	struct trust_anchor* ta;
	if(!(ta=anchor_store_new_key(anchors, rr,
		sldns_wirerr_get_type(rr, rl, dl),
		sldns_wirerr_get_class(rr, rl, dl),
		sldns_wirerr_get_rdatawl(rr, rl, dl),
		sldns_wirerr_get_rdatalen(rr, rl, dl)+2))) {
		return NULL;
	}
	log_nametypeclass(VERB_QUERY, "adding trusted key",
		rr, sldns_wirerr_get_type(rr, rl, dl),
		sldns_wirerr_get_class(rr, rl, dl));
	return ta;
}