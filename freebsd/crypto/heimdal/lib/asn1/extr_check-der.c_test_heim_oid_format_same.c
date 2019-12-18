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
typedef  int /*<<< orphan*/  heim_oid ;

/* Variables and functions */
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 int der_heim_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int der_parse_heim_oid (char*,char*,int /*<<< orphan*/ *) ; 
 int der_print_heim_oid (int /*<<< orphan*/  const*,char,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int strcmp (char*,char const*) ; 

__attribute__((used)) static int
test_heim_oid_format_same(const char *str, const heim_oid *oid)
{
    int ret;
    char *p;
    heim_oid o2;

    ret = der_print_heim_oid(oid, ' ', &p);
    if (ret) {
	printf("fail to print oid: %s\n", str);
	return 1;
    }
    ret = strcmp(p, str);
    if (ret) {
	printf("oid %s != formated oid %s\n", str, p);
	free(p);
	return ret;
    }

    ret = der_parse_heim_oid(p, " ", &o2);
    if (ret) {
	printf("failed to parse %s\n", p);
	free(p);
	return ret;
    }
    free(p);
    ret = der_heim_oid_cmp(&o2, oid);
    der_free_oid(&o2);

    return ret;
}