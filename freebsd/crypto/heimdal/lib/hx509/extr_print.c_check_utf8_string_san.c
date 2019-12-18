#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hx509_validate_ctx ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ heim_any ;
typedef  int PKIXXmppAddr ;

/* Variables and functions */
 int /*<<< orphan*/  HX509_VALIDATE_F_VALIDATE ; 
 int /*<<< orphan*/  HX509_VALIDATE_F_VERBOSE ; 
 int decode_PKIXXmppAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 int /*<<< orphan*/  free_PKIXXmppAddr (int*) ; 
 int /*<<< orphan*/  validate_print (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
check_utf8_string_san(hx509_validate_ctx ctx, heim_any *a)
{
    PKIXXmppAddr jid;
    size_t size;
    int ret;

    ret = decode_PKIXXmppAddr(a->data, a->length, &jid, &size);
    if (ret) {
	validate_print(ctx, HX509_VALIDATE_F_VALIDATE,
		       "Decoding JID in SAN failed: %d", ret);
	return 1;
    }

    validate_print(ctx, HX509_VALIDATE_F_VERBOSE, "%s", jid);
    free_PKIXXmppAddr(&jid);

    return 0;
}