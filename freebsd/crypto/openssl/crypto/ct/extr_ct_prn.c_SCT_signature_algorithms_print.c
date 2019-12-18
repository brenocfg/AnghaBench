#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sig_alg; int /*<<< orphan*/  hash_alg; } ;
typedef  TYPE_1__ SCT ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int NID_undef ; 
 int /*<<< orphan*/  OBJ_nid2ln (int) ; 
 int SCT_get_signature_nid (TYPE_1__ const*) ; 

__attribute__((used)) static void SCT_signature_algorithms_print(const SCT *sct, BIO *out)
{
    int nid = SCT_get_signature_nid(sct);

    if (nid == NID_undef)
        BIO_printf(out, "%02X%02X", sct->hash_alg, sct->sig_alg);
    else
        BIO_printf(out, "%s", OBJ_nid2ln(nid));
}