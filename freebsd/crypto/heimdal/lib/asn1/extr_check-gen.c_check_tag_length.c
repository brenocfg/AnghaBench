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
typedef  int /*<<< orphan*/  td ;
struct test_data {int member_0; int member_1; int member_2; char* member_3; scalar_t__ ok; size_t expected_len; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct map_page {int dummy; } ;
typedef  int TESTuint32 ;

/* Variables and functions */
 int /*<<< orphan*/  OVERRUN ; 
 int decode_TESTuint32 (void*,int /*<<< orphan*/ ,int*,size_t*) ; 
 void* map_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct map_page**) ; 
 int /*<<< orphan*/  map_free (struct map_page*,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
check_tag_length(void)
{
    struct test_data td[] = {
	{ 1, 3, 3, "\x02\x01\x00"},
	{ 1, 3, 3, "\x02\x01\x7f"},
	{ 1, 4, 4, "\x02\x02\x00\x80"},
	{ 1, 4, 4, "\x02\x02\x01\x00"},
	{ 1, 4, 4, "\x02\x02\x02\x00"},
	{ 0, 3, 0, "\x02\x02\x00"},
	{ 0, 3, 0, "\x02\x7f\x7f"},
	{ 0, 4, 0, "\x02\x03\x00\x80"},
	{ 0, 4, 0, "\x02\x7f\x01\x00"},
	{ 0, 5, 0, "\x02\xff\x7f\x02\x00"}
    };
    size_t sz;
    TESTuint32 values[] = {0, 127, 128, 256, 512,
			 0, 127, 128, 256, 512 };
    TESTuint32 u;
    int i, ret, failed = 0;
    void *buf;

    for (i = 0; i < sizeof(td)/sizeof(td[0]); i++) {
	struct map_page *page;

	buf = map_alloc(OVERRUN, td[i].data, td[i].len, &page);

	ret = decode_TESTuint32(buf, td[i].len, &u, &sz);
	if (ret) {
	    if (td[i].ok) {
		printf("failed with tag len test %d\n", i);
		failed = 1;
	    }
	} else {
	    if (td[i].ok == 0) {
		printf("failed with success for tag len test %d\n", i);
		failed = 1;
	    }
	    if (td[i].expected_len != sz) {
		printf("wrong expected size for tag test %d\n", i);
		failed = 1;
	    }
	    if (values[i] != u) {
		printf("wrong value for tag test %d\n", i);
		failed = 1;
	    }
	}
	map_free(page, "test", "decode");
    }
    return failed;
}