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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int BUFSIZE ; 
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int /*<<< orphan*/  const,int) ; 
 struct tm* gmtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  istr ; 
 scalar_t__ strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static int
ahcp_time_print(netdissect_options *ndo, const u_char *cp, const u_char *ep)
{
	time_t t;
	struct tm *tm;
	char buf[BUFSIZE];

	if (cp + 4 != ep)
		goto invalid;
	ND_TCHECK2(*cp, 4);
	t = EXTRACT_32BITS(cp);
	if (NULL == (tm = gmtime(&t)))
		ND_PRINT((ndo, ": gmtime() error"));
	else if (0 == strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm))
		ND_PRINT((ndo, ": strftime() error"));
	else
		ND_PRINT((ndo, ": %s UTC", buf));
	return 0;

invalid:
	ND_PRINT((ndo, "%s", istr));
	ND_TCHECK2(*cp, ep - cp);
	return 0;
trunc:
	ND_PRINT((ndo, "%s", tstr));
	return -1;
}