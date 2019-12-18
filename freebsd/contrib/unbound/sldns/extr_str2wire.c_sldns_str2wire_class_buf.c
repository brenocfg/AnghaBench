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
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL ; 
 int LDNS_WIREPARSE_ERR_OK ; 
 int LDNS_WIREPARSE_ERR_SYNTAX_CLASS ; 
 scalar_t__ sldns_get_rr_class_by_name (char const*) ; 
 int /*<<< orphan*/  sldns_write_uint16 (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int sldns_str2wire_class_buf(const char* str, uint8_t* rd, size_t* len)
{
	uint16_t c = sldns_get_rr_class_by_name(str);
	if(c == 0 && strcmp(str, "CLASS0") != 0)
		return LDNS_WIREPARSE_ERR_SYNTAX_CLASS;
	if(*len < 2)
		return LDNS_WIREPARSE_ERR_BUFFER_TOO_SMALL;
	sldns_write_uint16(rd, c);
	*len = 2;
	return LDNS_WIREPARSE_ERR_OK;
}