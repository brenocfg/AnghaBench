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
struct sldns_file_parse_state {int /*<<< orphan*/  default_ttl; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_str2period (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  sldns_strip_ws (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int
http_parse_ttl(sldns_buffer* buf, struct sldns_file_parse_state* pstate)
{
	char* line = (char*)sldns_buffer_begin(buf);
	if(strncmp(line, "$TTL", 4) == 0 &&
		isspace((unsigned char)line[4])) {
		const char* end = NULL;
		pstate->default_ttl = sldns_str2period(
			sldns_strip_ws(line+5), &end);
		return 1;
	}
	return 0;
}