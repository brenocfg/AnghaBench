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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int MAX_LENGTH_CANON ; 
 int _wind_stringprep_normalize (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  dump_vector (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t parse_vector (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static int
test(char *buf, unsigned lineno)
{
    char *last;
    char *c;
    uint32_t in[MAX_LENGTH_CANON];
    size_t in_len;
    uint32_t out[MAX_LENGTH_CANON];
    size_t out_len;
    uint32_t *tmp;
    size_t norm_len;
    int ret;

    c = strtok_r(buf, ";", &last);
    if (c == NULL)
	return 0;

    in_len = parse_vector(c, in);
    if (strtok_r(NULL, ";", &last) == NULL)
	return 0;
    if (strtok_r(NULL, ";", &last) == NULL)
	return 0;
    c = strtok_r(NULL, ";", &last);
    if (c == NULL)
	return 0;
    out_len = parse_vector(c, out);
    if (strtok_r(NULL, ";", &last) == NULL)
	return 0;
    c = last;

    norm_len = MAX_LENGTH_CANON;
    tmp = malloc(norm_len * sizeof(uint32_t));
    if (tmp == NULL && norm_len != 0)
	err(1, "malloc");
    ret = _wind_stringprep_normalize(in, in_len, tmp, &norm_len);
    if (ret) {
	printf("wind_stringprep_normalize %s failed\n", c);
	free(tmp);
	return 1;
    }
    if (out_len != norm_len) {
	printf("%u: wrong out len (%s)\n", lineno, c);
	dump_vector("Expected", out, out_len);
	dump_vector("Received", tmp, norm_len);
	free(tmp);
	return 1;
    }
    if (memcmp(out, tmp, out_len * sizeof(uint32_t)) != 0) {
	printf("%u: wrong out data (%s)\n", lineno, c);
	dump_vector("Expected", out, out_len);
	dump_vector("Received", tmp, norm_len);
	free(tmp);
	return 1;
    }
    free(tmp);
    return 0;
}