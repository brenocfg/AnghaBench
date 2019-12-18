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
struct ldp_msg_header {int dummy; } ;
struct ldp_common_header {int dummy; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int ldp_pdu_print (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

void
ldp_print(netdissect_options *ndo,
          register const u_char *pptr, register u_int len)
{
    int processed;
    while (len > (sizeof(struct ldp_common_header) + sizeof(struct ldp_msg_header))) {
        processed = ldp_pdu_print(ndo, pptr);
        if (processed == 0)
            return;
        len -= processed;
        pptr += processed;
    }
}