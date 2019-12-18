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
struct rerr {int code; char const* name; char* explain; } ;
typedef  int /*<<< orphan*/  regex_t ;
typedef  int /*<<< orphan*/  convbuf ;

/* Variables and functions */
 int REG_ATOI ; 
 int REG_ITOA ; 
 int /*<<< orphan*/  assert (int) ; 
 char* regatoi (int /*<<< orphan*/  const*,char*) ; 
 struct rerr* rerrs ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

size_t
regerror(int errcode,
	 const regex_t * __restrict preg,
	 char * __restrict errbuf,
	 size_t errbuf_size)
{
	struct rerr *r;
	size_t len;
	int target = errcode &~ REG_ITOA;
	const char *s;
	char convbuf[50];

	if (errcode == REG_ATOI)
		s = regatoi(preg, convbuf);
	else {
		for (r = rerrs; r->code != 0; r++)
			if (r->code == target)
				break;

		if (errcode&REG_ITOA) {
			if (r->code != 0)
				(void) strcpy(convbuf, r->name);
			else
				sprintf(convbuf, "REG_0x%x", target);
			assert(strlen(convbuf) < sizeof(convbuf));
			s = convbuf;
		} else
			s = r->explain;
	}

	len = strlen(s) + 1;
	if (errbuf_size > 0) {
		if (errbuf_size > len)
			(void) strcpy(errbuf, s);
		else {
			(void) strncpy(errbuf, s, errbuf_size-1);
			errbuf[errbuf_size-1] = '\0';
		}
	}

	return(len);
}