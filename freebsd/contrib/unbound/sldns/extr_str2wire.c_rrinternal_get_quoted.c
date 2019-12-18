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
typedef  int /*<<< orphan*/  sldns_rdf_type ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 char* sldns_buffer_current (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sldns_rdf_type_maybe_quoted (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rrinternal_get_quoted(sldns_buffer* strbuf, const char** delimiters,
	sldns_rdf_type rdftype)
{
	if(sldns_rdf_type_maybe_quoted(rdftype) &&
		sldns_buffer_remaining(strbuf) > 0) {

		/* skip spaces */
		while(sldns_buffer_remaining(strbuf) > 0 &&
			*(sldns_buffer_current(strbuf)) == ' ') {
			sldns_buffer_skip(strbuf, 1);
		}

		if(sldns_buffer_remaining(strbuf) > 0 &&
			*(sldns_buffer_current(strbuf)) == '\"') {
			*delimiters = "\"\0";
			sldns_buffer_skip(strbuf, 1);
			return 1;
		}
	}
	return 0;
}