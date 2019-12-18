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
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct tr_query {int /*<<< orphan*/  tr_rttlqid; int /*<<< orphan*/  tr_raddr; int /*<<< orphan*/  tr_dst; int /*<<< orphan*/  tr_src; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_32BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ IN_CLASSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct tr_query const) ; 
 int /*<<< orphan*/  TR_GETQID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TR_GETTTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tstr ; 

__attribute__((used)) static void
print_mtrace(netdissect_options *ndo,
             register const u_char *bp, register u_int len)
{
    register const struct tr_query *tr = (const struct tr_query *)(bp + 8);

    ND_TCHECK(*tr);
    if (len < 8 + sizeof (struct tr_query)) {
	ND_PRINT((ndo, " [invalid len %d]", len));
	return;
    }
    ND_PRINT((ndo, "mtrace %u: %s to %s reply-to %s",
        TR_GETQID(EXTRACT_32BITS(&tr->tr_rttlqid)),
        ipaddr_string(ndo, &tr->tr_src), ipaddr_string(ndo, &tr->tr_dst),
        ipaddr_string(ndo, &tr->tr_raddr)));
    if (IN_CLASSD(EXTRACT_32BITS(&tr->tr_raddr)))
        ND_PRINT((ndo, " with-ttl %d", TR_GETTTL(EXTRACT_32BITS(&tr->tr_rttlqid))));
    return;
trunc:
    ND_PRINT((ndo, "%s", tstr));
}