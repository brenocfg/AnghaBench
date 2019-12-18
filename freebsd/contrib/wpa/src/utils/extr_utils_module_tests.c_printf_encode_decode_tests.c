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
typedef  int u8 ;
struct printf_test_data {int const* data; int len; char* encoded; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  bin ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int int_array_len (int*) ; 
 int /*<<< orphan*/  int_array_sort_unique (int*) ; 
 scalar_t__ os_memcmp (int*,int const*,size_t) ; 
 int printf_decode (int*,int,char*) ; 
 int /*<<< orphan*/  printf_encode (char*,int,int const*,int) ; 
 struct printf_test_data* printf_tests ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int printf_encode_decode_tests(void)
{
	int i;
	size_t binlen;
	char buf[100];
	u8 bin[100];
	int errors = 0;
	int array[10];

	wpa_printf(MSG_INFO, "printf encode/decode tests");

	for (i = 0; printf_tests[i].data; i++) {
		const struct printf_test_data *test = &printf_tests[i];
		printf_encode(buf, sizeof(buf), test->data, test->len);
		wpa_printf(MSG_INFO, "%d: -> \"%s\"", i, buf);

		binlen = printf_decode(bin, sizeof(bin), buf);
		if (binlen != test->len ||
		    os_memcmp(bin, test->data, binlen) != 0) {
			wpa_hexdump(MSG_ERROR, "Error in decoding#1",
				    bin, binlen);
			errors++;
		}

		binlen = printf_decode(bin, sizeof(bin), test->encoded);
		if (binlen != test->len ||
		    os_memcmp(bin, test->data, binlen) != 0) {
			wpa_hexdump(MSG_ERROR, "Error in decoding#2",
				    bin, binlen);
			errors++;
		}
	}

	buf[5] = 'A';
	printf_encode(buf, 5, (const u8 *) "abcde", 5);
	if (buf[5] != 'A') {
		wpa_printf(MSG_ERROR, "Error in bounds checking#1");
		errors++;
	}

	for (i = 5; i < 10; i++) {
		buf[i] = 'A';
		printf_encode(buf, i, (const u8 *) "\xdd\xdd\xdd\xdd\xdd", 5);
		if (buf[i] != 'A') {
			wpa_printf(MSG_ERROR, "Error in bounds checking#2(%d)",
				   i);
			errors++;
		}
	}

	if (printf_decode(bin, 3, "abcde") != 2)
		errors++;

	if (printf_decode(bin, 3, "\\xa") != 1 || bin[0] != 10)
		errors++;

	if (printf_decode(bin, 3, "\\xq") != 1 || bin[0] != 'q')
		errors++;

	if (printf_decode(bin, 3, "\\a") != 1 || bin[0] != 'a')
		errors++;

	array[0] = 10;
	array[1] = 10;
	array[2] = 5;
	array[3] = 10;
	array[4] = 5;
	array[5] = 0;
	if (int_array_len(array) != 5)
		errors++;
	int_array_sort_unique(array);
	if (int_array_len(array) != 2)
		errors++;

	if (errors) {
		wpa_printf(MSG_ERROR, "%d printf test(s) failed", errors);
		return -1;
	}

	return 0;
}