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
typedef  int /*<<< orphan*/  ldns_rr_class ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* ldns_rr_class2str (int /*<<< orphan*/ ) ; 
 int printf (char*,char*) ; 

__attribute__((used)) static int
print_rr_class(ldns_rr_class cls) {
    char *str;
    int n;

    str = ldns_rr_class2str(cls);
    n = printf("%s", str);
    free(str);
    return n;
}