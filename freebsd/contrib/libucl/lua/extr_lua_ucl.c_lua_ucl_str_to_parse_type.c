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
typedef  enum ucl_parse_type { ____Placeholder_ucl_parse_type } ucl_parse_type ;

/* Variables and functions */
 int UCL_PARSE_AUTO ; 
 int UCL_PARSE_CSEXP ; 
 int UCL_PARSE_MSGPACK ; 
 int UCL_PARSE_UCL ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static inline enum ucl_parse_type
lua_ucl_str_to_parse_type (const char *str)
{
	enum ucl_parse_type type = UCL_PARSE_UCL;

	if (str != NULL) {
		if (strcasecmp (str, "msgpack") == 0) {
			type = UCL_PARSE_MSGPACK;
		}
		else if (strcasecmp (str, "sexp") == 0 ||
				strcasecmp (str, "csexp") == 0) {
			type = UCL_PARSE_CSEXP;
		}
		else if (strcasecmp (str, "auto") == 0) {
			type = UCL_PARSE_AUTO;
		}
	}

	return type;
}