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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int vsnprintf (char*,size_t,char const*,int /*<<< orphan*/ ) ; 

int sldns_str_vprint(char** str, size_t* slen, const char* format, va_list args)
{
	int w = vsnprintf(*str, *slen, format, args);
	if(w < 0) {
		/* error in printout */
		return 0;
	} else if((size_t)w >= *slen) {
		*str = NULL; /* we do not want str to point outside of buffer*/
		*slen = 0;
	} else {
		*str += w;
		*slen -= w;
	}
	return w;
}