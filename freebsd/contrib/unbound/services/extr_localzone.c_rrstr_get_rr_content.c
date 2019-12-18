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
typedef  scalar_t__ time_t ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_WIREPARSE_OFFSET (int) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/ * memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_get_errorstr_parse (int) ; 
 int sldns_str2wire_rr_buf (char const*,int /*<<< orphan*/ *,size_t*,size_t*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 
 int sldns_wirerr_get_rdatalen (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/ * sldns_wirerr_get_rdatawl (int /*<<< orphan*/ *,size_t,size_t) ; 
 scalar_t__ sldns_wirerr_get_ttl (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_wirerr_get_type (int /*<<< orphan*/ *,size_t,size_t) ; 

int
rrstr_get_rr_content(const char* str, uint8_t** nm, uint16_t* type,
	uint16_t* dclass, time_t* ttl, uint8_t* rr, size_t len,
	uint8_t** rdata, size_t* rdata_len)
{
	size_t dname_len = 0;
	int e = sldns_str2wire_rr_buf(str, rr, &len, &dname_len, 3600,
		NULL, 0, NULL, 0);
	if(e) {
		log_err("error parsing local-data at %d: '%s': %s",
			LDNS_WIREPARSE_OFFSET(e), str,
			sldns_get_errorstr_parse(e));
		return 0;
	}
	*nm = memdup(rr, dname_len);
	if(!*nm) {
		log_err("out of memory");
		return 0;
	}
	*dclass = sldns_wirerr_get_class(rr, len, dname_len);
	*type = sldns_wirerr_get_type(rr, len, dname_len);
	*ttl = (time_t)sldns_wirerr_get_ttl(rr, len, dname_len);
	*rdata = sldns_wirerr_get_rdatawl(rr, len, dname_len);
	*rdata_len = sldns_wirerr_get_rdatalen(rr, len, dname_len)+2;
	return 1;
}