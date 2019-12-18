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
struct testcase {char* str; int n; int* res; } ;

/* Variables and functions */
 int MAXSIZE ; 
 int _krb5_n_fold (char*,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ memcmp (unsigned char*,int*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 struct testcase* tests ; 

int
main(int argc, char **argv)
{
    unsigned char data[MAXSIZE];
    struct testcase *t;
    int ret = 0;

    for (t = tests; t->str; ++t) {
	int i;

	ret = _krb5_n_fold (t->str, strlen(t->str), data, t->n);
	if (ret)
	    errx(1, "out of memory");
	if (memcmp (data, t->res, t->n) != 0) {
	    printf ("n-fold(\"%s\", %d) failed\n", t->str, t->n);
	    printf ("should be: ");
	    for (i = 0; i < t->n; ++i)
		printf ("%02x", t->res[i]);
	    printf ("\nresult was: ");
	    for (i = 0; i < t->n; ++i)
		printf ("%02x", data[i]);
	    printf ("\n");
	    ret = 1;
	}
    }
    return ret;
}