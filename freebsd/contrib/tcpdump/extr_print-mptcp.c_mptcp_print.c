#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct mptcp_option {int /*<<< orphan*/  sub_etc; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
struct TYPE_2__ {int (* print ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPTCP_OPT_SUBTYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ MPTCP_SUB_FCLOSE ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int min (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* mptcp_options ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

int
mptcp_print(netdissect_options *ndo,
            const u_char *cp, u_int len, u_char flags)
{
        const struct mptcp_option *opt;
        u_int subtype;

        if (len < 3)
                return 0;

        opt = (const struct mptcp_option *) cp;
        subtype = min(MPTCP_OPT_SUBTYPE(opt->sub_etc), MPTCP_SUB_FCLOSE + 1);

        ND_PRINT((ndo, " %s", mptcp_options[subtype].name));
        return mptcp_options[subtype].print(ndo, cp, len, flags);
}