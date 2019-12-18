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
 size_t _heim_len_int (int) ; 
 int der_get_integer (unsigned char*,size_t,int*,size_t*) ; 
 int der_put_integer (unsigned char*,size_t,int*,size_t*) ; 
 unsigned char* emalloc (size_t) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
test_one_int(int val)
{
    int ret, dval;
    unsigned char *buf;
    size_t len_len, len;

    len = _heim_len_int(val);

    buf = emalloc(len + 2);

    buf[0] = '\xff';
    buf[len + 1] = '\xff';
    memset(buf + 1, 0, len);

    ret = der_put_integer(buf + 1 + len - 1, len, &val, &len_len);
    if (ret) {
	printf("integer %d encode failed %d\n", val, ret);
	return 1;
    }
    if (len != len_len) {
	printf("integer %d encode fail with %d len %lu, result len %lu\n",
	       val, ret, (unsigned long)len, (unsigned long)len_len);
	return 1;
    }

    ret = der_get_integer(buf + 1, len, &dval, &len_len);
    if (ret) {
	printf("integer %d decode failed %d\n", val, ret);
	return 1;
    }
    if (len != len_len) {
	printf("integer %d decoded diffrent len %lu != %lu",
	       val, (unsigned long)len, (unsigned long)len_len);
	return 1;
    }
    if (val != dval) {
	printf("decode decoded to diffrent value %d != %d",
	       val, dval);
	return 1;
    }

    if (buf[0] != (unsigned char)'\xff') {
	printf("precanary dead %d\n", val);
	return 1;
    }
    if (buf[len + 1] != (unsigned char)'\xff') {
	printf("postecanary dead %d\n", val);
	return 1;
    }
    free(buf);
    return 0;
}