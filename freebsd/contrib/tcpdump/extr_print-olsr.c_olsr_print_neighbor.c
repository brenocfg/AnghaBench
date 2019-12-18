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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TTEST2 (int /*<<< orphan*/  const,int) ; 
 int /*<<< orphan*/  ipaddr_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
olsr_print_neighbor(netdissect_options *ndo,
                    const u_char *msg_data, u_int hello_len)
{
    int neighbor;

    ND_PRINT((ndo, "\n\t      neighbor\n\t\t"));
    neighbor = 1;

    while (hello_len >= sizeof(struct in_addr)) {

        if (!ND_TTEST2(*msg_data, sizeof(struct in_addr)))
            return (-1);
        /* print 4 neighbors per line */

        ND_PRINT((ndo, "%s%s", ipaddr_string(ndo, msg_data),
               neighbor % 4 == 0 ? "\n\t\t" : " "));

        msg_data += sizeof(struct in_addr);
        hello_len -= sizeof(struct in_addr);
    }
    return (0);
}