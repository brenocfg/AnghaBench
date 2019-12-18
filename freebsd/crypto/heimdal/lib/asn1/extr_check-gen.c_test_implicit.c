#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; char* member_3; TYPE_2__* val; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/ * generic_copy ;
typedef  int /*<<< orphan*/  c0 ;
struct TYPE_4__ {int foo; } ;
struct TYPE_5__ {int ti3; TYPE_1__ ti2; scalar_t__ ti1; } ;
typedef  int /*<<< orphan*/  TESTImplicit2 ;
typedef  TYPE_2__ TESTImplicit ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_TESTImplicit ; 
 scalar_t__ copy_TESTImplicit ; 
 scalar_t__ decode_TESTImplicit ; 
 scalar_t__ decode_TESTImplicit2 ; 
 scalar_t__ encode_TESTImplicit ; 
 scalar_t__ encode_TESTImplicit2 ; 
 scalar_t__ free_TESTImplicit ; 
 scalar_t__ free_TESTImplicit2 ; 
 scalar_t__ generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ length_TESTImplicit ; 
 scalar_t__ length_TESTImplicit2 ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
test_implicit (void)
{
    struct test_case tests[] = {
	{ NULL,  16,
	  "\x30\x0e\x80\x01\x00\xa1\x06\xbf"
	  "\x7f\x03\x02\x01\x02\x82\x01\x03",
	  "implicit 1" }
    };

    int ret = 0, ntests = sizeof(tests) / sizeof(*tests);
    TESTImplicit c0;

    memset(&c0, 0, sizeof(c0));
    c0.ti1 = 0;
    c0.ti2.foo = 2;
    c0.ti3 = 3;
    tests[0].val = &c0;

    ret += generic_test (tests, ntests, sizeof(TESTImplicit),
			 (generic_encode)encode_TESTImplicit,
			 (generic_length)length_TESTImplicit,
			 (generic_decode)decode_TESTImplicit,
			 (generic_free)free_TESTImplicit,
			 cmp_TESTImplicit,
			 (generic_copy)copy_TESTImplicit);

#ifdef IMPLICIT_TAGGING_WORKS
    ret += generic_test (tests, ntests, sizeof(TESTImplicit2),
			 (generic_encode)encode_TESTImplicit2,
			 (generic_length)length_TESTImplicit2,
			 (generic_decode)decode_TESTImplicit2,
			 (generic_free)free_TESTImplicit2,
			 cmp_TESTImplicit,
			 NULL);

#endif /* IMPLICIT_TAGGING_WORKS */
    return ret;
}