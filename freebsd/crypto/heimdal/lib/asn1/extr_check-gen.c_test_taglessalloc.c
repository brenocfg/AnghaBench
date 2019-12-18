#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tests ;
struct test_case {int member_1; char* member_2; char* member_3; TYPE_2__* val; int /*<<< orphan*/ * member_0; } ;
struct TYPE_6__ {char* data; int length; } ;
typedef  TYPE_1__ heim_any ;
typedef  int /*<<< orphan*/  generic_length ;
typedef  int /*<<< orphan*/  generic_free ;
typedef  int /*<<< orphan*/  generic_encode ;
typedef  int /*<<< orphan*/  generic_decode ;
typedef  int /*<<< orphan*/  generic_copy ;
typedef  int /*<<< orphan*/  c3 ;
typedef  int /*<<< orphan*/  c2 ;
typedef  int /*<<< orphan*/  c1 ;
struct TYPE_8__ {int ai; } ;
struct TYPE_7__ {int three; TYPE_4__* tagless; TYPE_1__* tagless2; } ;
typedef  TYPE_2__ TESTAlloc ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_TESTAlloc ; 
 scalar_t__ copy_TESTAlloc ; 
 scalar_t__ decode_TESTAlloc ; 
 TYPE_4__* ecalloc (int,int) ; 
 scalar_t__ encode_TESTAlloc ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 scalar_t__ free_TESTAlloc ; 
 scalar_t__ generic_test (struct test_case*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ length_TESTAlloc ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
test_taglessalloc (void)
{
    struct test_case tests[] = {
	{ NULL,  14,
	  "\x30\x0c\x30\x05\xa0\x03\x02\x01\x01\xa1\x03\x02\x01\x03",
	  "alloc 1" },
	{ NULL,  7,
	  "\x30\x05\xa1\x03\x02\x01\x03",
	  "alloc 2" },
	{ NULL,  10,
	  "\x30\x08\xa1\x03\x02\x01\x04\x02\x01\x05",
	  "alloc 3" }
    };

    int ret = 0, ntests = sizeof(tests) / sizeof(*tests);
    TESTAlloc c1, c2, c3;
    heim_any any3;

    memset(&c1, 0, sizeof(c1));
    c1.tagless = ecalloc(1, sizeof(*c1.tagless));
    c1.tagless->ai = 1;
    c1.three = 3;
    tests[0].val = &c1;

    memset(&c2, 0, sizeof(c2));
    c2.tagless = NULL;
    c2.three = 3;
    tests[1].val = &c2;

    memset(&c3, 0, sizeof(c3));
    c3.tagless = NULL;
    c3.three = 4;
    c3.tagless2 = &any3;
    any3.data = "\x02\x01\x05";
    any3.length = 3;
    tests[2].val = &c3;

    ret += generic_test (tests, ntests, sizeof(TESTAlloc),
			 (generic_encode)encode_TESTAlloc,
			 (generic_length)length_TESTAlloc,
			 (generic_decode)decode_TESTAlloc,
			 (generic_free)free_TESTAlloc,
			 cmp_TESTAlloc,
			 (generic_copy)copy_TESTAlloc);

    free(c1.tagless);

    return ret;
}