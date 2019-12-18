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
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {int /*<<< orphan*/  const* ndo_snapend; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 scalar_t__ MAX_RST_DATA_LEN ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 scalar_t__ ND_TTEST2 (int /*<<< orphan*/  const,scalar_t__) ; 
 int /*<<< orphan*/  safeputchar (TYPE_1__*,int) ; 

__attribute__((used)) static void
print_tcp_rst_data(netdissect_options *ndo,
                   register const u_char *sp, u_int length)
{
        int c;

        ND_PRINT((ndo, ND_TTEST2(*sp, length) ? " [RST" : " [!RST"));
        if (length > MAX_RST_DATA_LEN) {
                length = MAX_RST_DATA_LEN;	/* can use -X for longer */
                ND_PRINT((ndo, "+"));			/* indicate we truncate */
        }
        ND_PRINT((ndo, " "));
        while (length-- && sp < ndo->ndo_snapend) {
                c = *sp++;
                safeputchar(ndo, c);
        }
        ND_PRINT((ndo, "]"));
}