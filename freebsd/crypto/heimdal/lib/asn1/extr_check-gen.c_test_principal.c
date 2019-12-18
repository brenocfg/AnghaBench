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
struct TYPE_5__ {int member_0; int /*<<< orphan*/  member_1; } ;
struct TYPE_4__ {TYPE_2__ member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {char* member_1; TYPE_1__ member_0; } ;
typedef  TYPE_3__ Principal ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_NT_PRINCIPAL ; 
 int /*<<< orphan*/  KRB5_NT_SRV_HST ; 
 scalar_t__ asprintf (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  cmp_principal ; 
 int /*<<< orphan*/  datan_princ ; 
 scalar_t__ decode_Principal ; 
 scalar_t__ encode_Principal ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ free_Principal ; 
 int generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ length_Principal ; 
 int /*<<< orphan*/  lha_principal ; 
 int /*<<< orphan*/  lharoot_princ ; 

__attribute__((used)) static int
test_principal (void)
{

    struct test_case tests[] = {
	{ NULL, 29,
	  "\x30\x1b\xa0\x10\x30\x0e\xa0\x03\x02\x01\x01\xa1\x07\x30\x05\x1b"
	  "\x03\x6c\x68\x61\xa1\x07\x1b\x05\x53\x55\x2e\x53\x45"
	},
	{ NULL, 35,
	  "\x30\x21\xa0\x16\x30\x14\xa0\x03\x02\x01\x01\xa1\x0d\x30\x0b\x1b"
	  "\x03\x6c\x68\x61\x1b\x04\x72\x6f\x6f\x74\xa1\x07\x1b\x05\x53\x55"
	  "\x2e\x53\x45"
	},
	{ NULL, 54,
	  "\x30\x34\xa0\x26\x30\x24\xa0\x03\x02\x01\x03\xa1\x1d\x30\x1b\x1b"
	  "\x04\x68\x6f\x73\x74\x1b\x13\x6e\x75\x74\x63\x72\x61\x63\x6b\x65"
	  "\x72\x2e\x65\x2e\x6b\x74\x68\x2e\x73\x65\xa1\x0a\x1b\x08\x45\x2e"
	  "\x4b\x54\x48\x2e\x53\x45"
	}
    };


    Principal values[] = {
	{ { KRB5_NT_PRINCIPAL, { 1, lha_principal } },  "SU.SE" },
	{ { KRB5_NT_PRINCIPAL, { 2, lharoot_princ } },  "SU.SE" },
	{ { KRB5_NT_SRV_HST, { 2, datan_princ } },  "E.KTH.SE" }
    };
    int i, ret;
    int ntests = sizeof(tests) / sizeof(*tests);

    for (i = 0; i < ntests; ++i) {
	tests[i].val = &values[i];
	if (asprintf (&tests[i].name, "Principal %d", i) < 0)
	    errx(1, "malloc");
	if (tests[i].name == NULL)
	    errx(1, "malloc");
    }

    ret = generic_test (tests, ntests, sizeof(Principal),
			(generic_encode)encode_Principal,
			(generic_length)length_Principal,
			(generic_decode)decode_Principal,
			(generic_free)free_Principal,
			cmp_principal,
			NULL);
    for (i = 0; i < ntests; ++i)
	free (tests[i].name);

    return ret;
}