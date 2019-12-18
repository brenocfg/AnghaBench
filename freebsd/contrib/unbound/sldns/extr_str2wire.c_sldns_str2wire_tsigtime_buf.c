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
typedef  int uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_SYNTAX_TIME ; 
 int RET_ERR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_write_uint16 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  sldns_write_uint32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

int sldns_str2wire_tsigtime_buf(const char* str, uint8_t* rd, size_t* len)
{
	char* end;
	uint64_t t = (uint64_t)strtol((char*)str, &end, 10);
	uint16_t high;
	uint32_t low;
	if(*end != 0)
		return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX_TIME, end-str);
	if(*len < 6)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	high = (uint16_t)(t>>32);
	low = (uint32_t)(t);
	sldns_write_uint16(rd, high);
	sldns_write_uint32(rd+2, low);
	*len = 6;
	return LDNS_WIREPARSE_ERR_OK;
}