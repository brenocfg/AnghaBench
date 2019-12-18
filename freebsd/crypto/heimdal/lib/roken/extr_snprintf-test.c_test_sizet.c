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
typedef  int /*<<< orphan*/  sizet_values ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  rk_snprintf (char*,int,char*,size_t) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ try (char*,size_t) ; 

__attribute__((used)) static int
test_sizet (void)
{
    int tot = 0;
    size_t sizet_values[] = { 0, 1, 2, 200, 4294967295u }; /* SIZE_MAX */
    char *result[] = { "0", "1", "2", "200", "4294967295" };
    int i;

    for (i = 0; i < sizeof(sizet_values) / sizeof(sizet_values[0]); ++i) {
#if 0
	tot += try("%zu", sizet_values[i]);
	tot += try("%zx", sizet_values[i]);
	tot += try("%zX", sizet_values[i]);
#else
	char buf[256];
	rk_snprintf(buf, sizeof(buf), "%zu", sizet_values[i]);
	if (strcmp(buf, result[i]) != 0) {
	    printf("%s != %s", buf, result[i]);
	    tot++;
	}
#endif
    }
    return tot;
}