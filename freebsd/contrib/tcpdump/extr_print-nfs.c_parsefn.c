#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (int const,int) ; 
 int /*<<< orphan*/  NTOHL (int) ; 
 scalar_t__ fn_printn (TYPE_1__*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const uint32_t *
parsefn(netdissect_options *ndo,
        register const uint32_t *dp)
{
	register uint32_t len;
	register const u_char *cp;

	/* Bail if we don't have the string length */
	ND_TCHECK(*dp);

	/* Fetch string length; convert to host order */
	len = *dp++;
	NTOHL(len);

	ND_TCHECK2(*dp, ((len + 3) & ~3));

	cp = (const u_char *)dp;
	/* Update 32-bit pointer (NFS filenames padded to 32-bit boundaries) */
	dp += ((len + 3) & ~3) / sizeof(*dp);
	ND_PRINT((ndo, "\""));
	if (fn_printn(ndo, cp, len, ndo->ndo_snapend)) {
		ND_PRINT((ndo, "\""));
		goto trunc;
	}
	ND_PRINT((ndo, "\""));

	return (dp);
trunc:
	return NULL;
}