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
typedef  int /*<<< orphan*/  nm ;
typedef  int /*<<< orphan*/  RES ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_OFFSET (int) ; 
 int dname_count_size_labels (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/ * memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sldns_get_errorstr_parse (int) ; 
 int sldns_str2wire_dname_buf (char*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  ssl_printf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
parse_arg_name(RES* ssl, char* str, uint8_t** res, size_t* len, int* labs)
{
	uint8_t nm[LDNS_MAX_DOMAINLEN+1];
	size_t nmlen = sizeof(nm);
	int status;
	*res = NULL;
	*len = 0;
	*labs = 0;
	status = sldns_str2wire_dname_buf(str, nm, &nmlen);
	if(status != 0) {
		ssl_printf(ssl, "error cannot parse name %s at %d: %s\n", str,
			LDNS_WIREPARSE_OFFSET(status),
			sldns_get_errorstr_parse(status));
		return 0;
	}
	*res = memdup(nm, nmlen);
	if(!*res) {
		ssl_printf(ssl, "error out of memory\n");
		return 0;
	}
	*labs = dname_count_size_labels(*res, len);
	return 1;
}