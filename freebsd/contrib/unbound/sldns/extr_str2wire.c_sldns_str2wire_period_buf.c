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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int /*<<< orphan*/  LDNS_WIREPARSE_ERR_SYNTAX_PERIOD ; 
 int RET_ERR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_str2period (char const*,char const**) ; 
 int /*<<< orphan*/  sldns_write_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sldns_str2wire_period_buf(const char* str, uint8_t* rd, size_t* len)
{
	const char* end;
	uint32_t p = sldns_str2period(str, &end);
	if(*end != 0)
		return RET_ERR(LDNS_WIREPARSE_ERR_SYNTAX_PERIOD, end-str);
	if(*len < 4)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	sldns_write_uint32(rd, p);
	*len = 4;
	return LDNS_WIREPARSE_ERR_OK;
}