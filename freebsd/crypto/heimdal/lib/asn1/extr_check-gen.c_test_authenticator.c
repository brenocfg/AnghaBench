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
struct test_case {int member_1; char* member_2; int /*<<< orphan*/ * name; TYPE_3__* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
struct TYPE_5__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_4__ {TYPE_2__ member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int member_0; char* member_1; int member_4; int member_5; int /*<<< orphan*/ * member_8; int /*<<< orphan*/ * member_7; int /*<<< orphan*/ * member_6; int /*<<< orphan*/ * member_3; TYPE_1__ member_2; } ;
typedef  TYPE_3__ Authenticator ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_NT_PRINCIPAL ; 
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  cmp_authenticator ; 
 scalar_t__ copy_Authenticator ; 
 scalar_t__ decode_Authenticator ; 
 scalar_t__ encode_Authenticator ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ free_Authenticator ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_Authenticator ; 
 int /*<<< orphan*/  lha_principal ; 
 int /*<<< orphan*/  lharoot_princ ; 

__attribute__((used)) static int
test_authenticator (void)
{
    struct test_case tests[] = {
	{ NULL, 63,
	  "\x62\x3d\x30\x3b\xa0\x03\x02\x01\x05\xa1\x0a\x1b\x08"
	  "\x45\x2e\x4b\x54\x48\x2e\x53\x45\xa2\x10\x30\x0e\xa0"
	  "\x03\x02\x01\x01\xa1\x07\x30\x05\x1b\x03\x6c\x68\x61"
	  "\xa4\x03\x02\x01\x0a\xa5\x11\x18\x0f\x31\x39\x37\x30"
	  "\x30\x31\x30\x31\x30\x30\x30\x31\x33\x39\x5a"
	},
	{ NULL, 67,
	  "\x62\x41\x30\x3f\xa0\x03\x02\x01\x05\xa1\x07\x1b\x05"
	  "\x53\x55\x2e\x53\x45\xa2\x16\x30\x14\xa0\x03\x02\x01"
	  "\x01\xa1\x0d\x30\x0b\x1b\x03\x6c\x68\x61\x1b\x04\x72"
	  "\x6f\x6f\x74\xa4\x04\x02\x02\x01\x24\xa5\x11\x18\x0f"
	  "\x31\x39\x37\x30\x30\x31\x30\x31\x30\x30\x31\x36\x33"
	  "\x39\x5a"
	}
    };

    Authenticator values[] = {
	{ 5, "E.KTH.SE", { KRB5_NT_PRINCIPAL, { 1, lha_principal } },
	  NULL, 10, 99, NULL, NULL, NULL },
	{ 5, "SU.SE", { KRB5_NT_PRINCIPAL, { 2, lharoot_princ } },
	  NULL, 292, 999, NULL, NULL, NULL }
    };
    int i, ret;
    int ntests = sizeof(tests) / sizeof(*tests);

    for (i = 0; i < ntests; ++i) {
	tests[i].val = &values[i];
	if (asprintf (&tests[i].name, "Authenticator %d", i) < 0)
	    errx(1, "malloc");
	if (tests[i].name == NULL)
	    errx(1, "malloc");
    }

    ret = generic_test (tests, ntests, sizeof(Authenticator),
			(generic_encode)encode_Authenticator,
			(generic_length)length_Authenticator,
			(generic_decode)decode_Authenticator,
			(generic_free)free_Authenticator,
			cmp_authenticator,
			(generic_copy)copy_Authenticator);
    for (i = 0; i < ntests; ++i)
	free(tests[i].name);

    return ret;
}