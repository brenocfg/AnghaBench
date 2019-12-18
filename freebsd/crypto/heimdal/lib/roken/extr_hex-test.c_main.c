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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hex_decode (char*,...) ; 
 int hex_encode (void*,size_t,char**) ; 
 scalar_t__ memcmp (char*,void*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

int
main(int argc, char **argv)
{
    int numerr = 0;
    int numtest = 1;
    struct test {
	void *data;
	size_t len;
	const char *result;
    } *t, tests[] = {
	{ "", 0 , "" },
	{ "a", 1, "61" },
	{ "ab", 2, "6162" },
	{ "abc", 3, "616263" },
	{ "abcd", 4, "61626364" },
	{ "abcde", 5, "6162636465" },
	{ "abcdef", 6, "616263646566" },
	{ "abcdefg", 7, "61626364656667" },
	{ "=", 1, "3D" },
	{ NULL }
    };
    for(t = tests; t->data; t++) {
	char *str;
	int len;
	len = hex_encode(t->data, t->len, &str);
	if(strcmp(str, t->result) != 0) {
	    fprintf(stderr, "failed test %d: %s != %s\n", numtest,
		    str, t->result);
	    numerr++;
	}
	free(str);
	str = strdup(t->result);
	len = strlen(str);
	len = hex_decode(t->result, str, len);
	if(len != t->len) {
	    fprintf(stderr, "failed test %d: len %lu != %lu\n", numtest,
		    (unsigned long)len, (unsigned long)t->len);
	    numerr++;
	} else if(memcmp(str, t->data, t->len) != 0) {
	    fprintf(stderr, "failed test %d: data\n", numtest);
	    numerr++;
	}
	free(str);
	numtest++;
    }

    {
	unsigned char buf[2] = { 0, 0xff } ;
	int len;

	len = hex_decode("A", buf, 1);
	if (len != 1) {
	    fprintf(stderr, "len != 1");
	    numerr++;
	}
	if (buf[0] != 10) {
	    fprintf(stderr, "buf != 10");
	    numerr++;
	}
	if (buf[1] != 0xff) {
	    fprintf(stderr, "buf != 0xff");
	    numerr++;
	}

    }

    return numerr;
}