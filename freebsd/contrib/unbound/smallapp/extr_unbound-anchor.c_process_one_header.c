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

/* Variables and functions */
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 int verb ; 

__attribute__((used)) static int
process_one_header(char* buf, size_t* clen, int* chunked)
{
	if(verb>=2) printf("header: '%s'\n", buf);
	if(strncasecmp(buf, "HTTP/1.1 ", 9) == 0) {
		/* check returncode */
		if(buf[9] != '2') {
			if(verb) printf("bad status %s\n", buf+9);
			return 0;
		}
	} else if(strncasecmp(buf, "Content-Length: ", 16) == 0) {
		if(!*chunked)
			*clen = (size_t)atoi(buf+16);
	} else if(strncasecmp(buf, "Transfer-Encoding: chunked", 19+7) == 0) {
		*clen = 0;
		*chunked = 1;
	}
	return 1;
}