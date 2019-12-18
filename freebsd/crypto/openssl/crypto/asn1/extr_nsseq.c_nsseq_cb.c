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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ NETSCAPE_CERT_SEQUENCE ;
typedef  int /*<<< orphan*/  ASN1_VALUE ;
typedef  int /*<<< orphan*/  ASN1_ITEM ;

/* Variables and functions */
 int ASN1_OP_NEW_POST ; 
 int /*<<< orphan*/  NID_netscape_cert_sequence ; 
 int /*<<< orphan*/  OBJ_nid2obj (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nsseq_cb(int operation, ASN1_VALUE **pval, const ASN1_ITEM *it,
                    void *exarg)
{
    if (operation == ASN1_OP_NEW_POST) {
        NETSCAPE_CERT_SEQUENCE *nsseq;
        nsseq = (NETSCAPE_CERT_SEQUENCE *)*pval;
        nsseq->type = OBJ_nid2obj(NID_netscape_cert_sequence);
    }
    return 1;
}