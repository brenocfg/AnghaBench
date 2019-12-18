#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {scalar_t__ id; } ;
typedef  TYPE_1__ sldns_lookup_table ;

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 TYPE_1__* sldns_lookup_by_name (int /*<<< orphan*/ ,char const*) ; 
 int sldns_str2wire_int16_buf (char const*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  sldns_tsig_errors ; 
 int /*<<< orphan*/  sldns_write_uint16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sldns_str2wire_tsigerror_buf(const char* str, uint8_t* rd, size_t* len)
{
	sldns_lookup_table *lt = sldns_lookup_by_name(sldns_tsig_errors, str);
	if(*len < 2)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	if(lt) {
		sldns_write_uint16(rd, (uint16_t)lt->id);
		*len = 2;
	} else {
		/* try as-is (a number) */
		return sldns_str2wire_int16_buf(str, rd, len);
	}
	return LDNS_WIREPARSE_ERR_OK;
}