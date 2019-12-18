#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; char* member_3; TYPE_3__* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
struct TYPE_4__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_5__ {int member_0; TYPE_1__ member_1; } ;
struct TYPE_6__ {int pvno; int msg_type; int stime; int susec; int error_code; char** crealm; char* realm; int /*<<< orphan*/ * e_data; int /*<<< orphan*/ * e_text; TYPE_2__ sname; TYPE_2__* cname; int /*<<< orphan*/ * cusec; int /*<<< orphan*/ * ctime; } ;
typedef  TYPE_2__ PrincipalName ;
typedef  TYPE_3__ KRB_ERROR ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_KRB_ERROR ; 
 scalar_t__ copy_KRB_ERROR ; 
 scalar_t__ decode_KRB_ERROR ; 
 scalar_t__ encode_KRB_ERROR ; 
 scalar_t__ free_KRB_ERROR ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_KRB_ERROR ; 
 int /*<<< orphan*/  lha_principal ; 
 int /*<<< orphan*/  nada_tgt_principal ; 

__attribute__((used)) static int
test_krb_error (void)
{
    struct test_case tests[] = {
	{ NULL, 127,
	  "\x7e\x7d\x30\x7b\xa0\x03\x02\x01\x05\xa1\x03\x02\x01\x1e\xa4\x11"
	  "\x18\x0f\x32\x30\x30\x33\x31\x31\x32\x34\x30\x30\x31\x31\x31\x39"
	  "\x5a\xa5\x05\x02\x03\x04\xed\xa5\xa6\x03\x02\x01\x1f\xa7\x0d\x1b"
	  "\x0b\x4e\x41\x44\x41\x2e\x4b\x54\x48\x2e\x53\x45\xa8\x10\x30\x0e"
	  "\xa0\x03\x02\x01\x01\xa1\x07\x30\x05\x1b\x03\x6c\x68\x61\xa9\x0d"
	  "\x1b\x0b\x4e\x41\x44\x41\x2e\x4b\x54\x48\x2e\x53\x45\xaa\x20\x30"
	  "\x1e\xa0\x03\x02\x01\x01\xa1\x17\x30\x15\x1b\x06\x6b\x72\x62\x74"
	  "\x67\x74\x1b\x0b\x4e\x41\x44\x41\x2e\x4b\x54\x48\x2e\x53\x45",
	  "KRB-ERROR Test 1"
	}
    };
    int ntests = sizeof(tests) / sizeof(*tests);
    KRB_ERROR e1;
    PrincipalName lhaprincipalname = { 1, { 1, lha_principal } };
    PrincipalName tgtprincipalname = { 1, { 2, nada_tgt_principal } };
    char *realm = "NADA.KTH.SE";

    e1.pvno = 5;
    e1.msg_type = 30;
    e1.ctime = NULL;
    e1.cusec = NULL;
    e1.stime = 1069632679;
    e1.susec = 322981;
    e1.error_code = 31;
    e1.crealm = &realm;
    e1.cname = &lhaprincipalname;
    e1.realm = "NADA.KTH.SE";
    e1.sname = tgtprincipalname;
    e1.e_text = NULL;
    e1.e_data = NULL;

    tests[0].val = &e1;

    return generic_test (tests, ntests, sizeof(KRB_ERROR),
			 (generic_encode)encode_KRB_ERROR,
			 (generic_length)length_KRB_ERROR,
			 (generic_decode)decode_KRB_ERROR,
			 (generic_free)free_KRB_ERROR,
			 cmp_KRB_ERROR,
			 (generic_copy)copy_KRB_ERROR);
}