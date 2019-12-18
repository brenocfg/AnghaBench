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
 int base64_decode (char*,char*) ; 
 int base64_encode (void*,size_t,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ memcmp (char*,void*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char const*) ; 
 char* strdup (char*) ; 

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
	{ "1", 1, "MQ==" },
	{ "22", 2, "MjI=" },
	{ "333", 3, "MzMz" },
	{ "4444", 4, "NDQ0NA==" },
	{ "55555", 5, "NTU1NTU=" },
	{ "abc:def", 7, "YWJjOmRlZg==" },
	{ NULL }
    };
    for(t = tests; t->data; t++) {
	char *str;
	int len;
	len = base64_encode(t->data, t->len, &str);
	if(strcmp(str, t->result) != 0) {
	    fprintf(stderr, "failed test %d: %s != %s\n", numtest,
		    str, t->result);
	    numerr++;
	}
	free(str);
	str = strdup(t->result);
	len = base64_decode(t->result, str);
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
	char str[32];
	if(base64_decode("M=M=", str) != -1) {
	    fprintf(stderr, "failed test %d: successful decode of `M=M='\n",
		    numtest++);
	    numerr++;
	}
	if(base64_decode("MQ===", str) != -1) {
	    fprintf(stderr, "failed test %d: successful decode of `MQ==='\n",
		    numtest++);
	    numerr++;
	}
    }
    return numerr;
}