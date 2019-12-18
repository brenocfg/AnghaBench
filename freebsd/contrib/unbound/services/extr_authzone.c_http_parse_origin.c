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
struct sldns_file_parse_state {int origin_len; int /*<<< orphan*/  origin; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int sldns_str2wire_dname_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sldns_strip_ws (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
http_parse_origin(sldns_buffer* buf, struct sldns_file_parse_state* pstate)
{
	char* line = (char*)sldns_buffer_begin(buf);
	if(strncmp(line, "$ORIGIN", 7) == 0 &&
		isspace((unsigned char)line[7])) {
		int s;
		pstate->origin_len = sizeof(pstate->origin);
		s = sldns_str2wire_dname_buf(sldns_strip_ws(line+8),
			pstate->origin, &pstate->origin_len);
		if(s) pstate->origin_len = 0;
		return 1;
	}
	return 0;
}