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
typedef  int /*<<< orphan*/  tests ;
typedef  int /*<<< orphan*/  Der_type ;
typedef  int /*<<< orphan*/  Der_class ;

/* Variables and functions */
 int der_get_tag (unsigned char const*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,size_t*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 

__attribute__((used)) static int
corner_tag(void)
{
    struct {
	int ok;
	const char *ptr;
	size_t len;
    } tests[] = {
	{ 1, "\x00", 1 },
	{ 0, "\xff", 1 },
	{ 0, "\xff\xff\xff\xff\xff\xff\xff\xff", 8 }
    };
    int i, ret;
    Der_class cl;
    Der_type ty;
    unsigned int tag;
    size_t size;

    for (i = 0; i < sizeof(tests)/sizeof(tests[0]); i++) {
	ret = der_get_tag((const unsigned char*)tests[i].ptr,
			  tests[i].len, &cl, &ty, &tag, &size);
	if (ret) {
	    if (tests[i].ok)
		errx(1, "failed while shouldn't");
	} else {
	    if (!tests[i].ok)
		errx(1, "passed while shouldn't");
	}
    }
    return 0;
}