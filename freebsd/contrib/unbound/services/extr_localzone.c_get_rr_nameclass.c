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
typedef  int /*<<< orphan*/  rr ;

/* Variables and functions */
 int LDNS_RR_BUF_SIZE ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_OFFSET (int) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/ * memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_get_errorstr_parse (int) ; 
 int sldns_str2wire_rr_buf (char const*,int /*<<< orphan*/ *,size_t*,size_t*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_wirerr_get_class (int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  sldns_wirerr_get_type (int /*<<< orphan*/ *,size_t,size_t) ; 

__attribute__((used)) static int
get_rr_nameclass(const char* str, uint8_t** nm, uint16_t* dclass,
	uint16_t* dtype)
{
	uint8_t rr[LDNS_RR_BUF_SIZE];
	size_t len = sizeof(rr), dname_len = 0;
	int s = sldns_str2wire_rr_buf(str, rr, &len, &dname_len, 3600,
		NULL, 0, NULL, 0);
	if(s != 0) {
		log_err("error parsing local-data at %d '%s': %s",
			LDNS_WIREPARSE_OFFSET(s), str,
			sldns_get_errorstr_parse(s));
		return 0;
	}
	*nm = memdup(rr, dname_len);
	*dclass = sldns_wirerr_get_class(rr, len, dname_len);
	*dtype = sldns_wirerr_get_type(rr, len, dname_len);
	if(!*nm) {
		log_err("out of memory");
		return 0;
	}
	return 1;
}