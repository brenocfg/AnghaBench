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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ldns_rdf ;

/* Variables and functions */
 int LDNS_IP6ADDRLEN ; 
 char* alloca (int) ; 
 int /*<<< orphan*/ * ldns_dname_new_frm_str (char*) ; 
 int* ldns_rdf_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static ldns_rdf *
ldns_rdf_reverse_aaaa(ldns_rdf *addr, const char *base) {
    char *buf;
    int i, len;

    len = strlen(base);
    buf = alloca(LDNS_IP6ADDRLEN*4 + len + 1);
    for (i = 0; i < LDNS_IP6ADDRLEN; i++) {
        uint8_t byte = ldns_rdf_data(addr)[LDNS_IP6ADDRLEN - i - 1];
        sprintf(&buf[i*4], "%x.%x.", byte & 0x0F, byte >> 4);
    }
    sprintf(&buf[LDNS_IP6ADDRLEN*4], "%s", base);
    return ldns_dname_new_frm_str(buf);
}