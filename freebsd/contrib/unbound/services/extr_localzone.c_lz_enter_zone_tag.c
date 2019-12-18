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
typedef  int /*<<< orphan*/  uint16_t ;
struct local_zones {int /*<<< orphan*/  lock; } ;
struct local_zone {size_t taglen; int /*<<< orphan*/  lock; scalar_t__ taglist; } ;
typedef  int /*<<< orphan*/  dname ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int dname_count_labels (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 struct local_zone* local_zones_find (struct local_zones*,int /*<<< orphan*/ *,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_rw_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_rw_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,char*) ; 
 scalar_t__ memdup (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ sldns_str2wire_dname_buf (char*,int /*<<< orphan*/ *,size_t*) ; 

__attribute__((used)) static int
lz_enter_zone_tag(struct local_zones* zones, char* zname, uint8_t* list,
	size_t len, uint16_t rr_class)
{
	uint8_t dname[LDNS_MAX_DOMAINLEN+1];
	size_t dname_len = sizeof(dname);
	int dname_labs, r = 0;
	struct local_zone* z;

	if(sldns_str2wire_dname_buf(zname, dname, &dname_len) != 0) {
		log_err("cannot parse zone name in local-zone-tag: %s", zname);
		return 0;
	}
	dname_labs = dname_count_labels(dname);
	
	lock_rw_rdlock(&zones->lock);
	z = local_zones_find(zones, dname, dname_len, dname_labs, rr_class);
	if(!z) {
		lock_rw_unlock(&zones->lock);
		log_err("no local-zone for tag %s", zname);
		return 0;
	}
	lock_rw_wrlock(&z->lock);
	lock_rw_unlock(&zones->lock);
	free(z->taglist);
	z->taglist = memdup(list, len);
	z->taglen = len;
	if(z->taglist)
		r = 1;
	lock_rw_unlock(&z->lock);
	return r;
}