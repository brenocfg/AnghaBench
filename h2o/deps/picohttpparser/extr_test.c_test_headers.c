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
struct phr_header {int /*<<< orphan*/  value_len; int /*<<< orphan*/  value; int /*<<< orphan*/  name_len; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE (char*,int,int,char*) ; 
 int bufis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int) ; 

__attribute__((used)) static void test_headers(void)
{
    /* only test the interface; the core parser is tested by the tests above */

    struct phr_header headers[4];
    size_t num_headers;

#define PARSE(s, last_len, exp, comment)                                                                                           \
    do {                                                                                                                           \
        note(comment);                                                                                                             \
        num_headers = sizeof(headers) / sizeof(headers[0]);                                                                        \
        ok(phr_parse_headers(s, strlen(s), headers, &num_headers, last_len) == (exp == 0 ? strlen(s) : exp));                      \
    } while (0)

    PARSE("Host: example.com\r\nCookie: \r\n\r\n", 0, 0, "simple");
    ok(num_headers == 2);
    ok(bufis(headers[0].name, headers[0].name_len, "Host"));
    ok(bufis(headers[0].value, headers[0].value_len, "example.com"));
    ok(bufis(headers[1].name, headers[1].name_len, "Cookie"));
    ok(bufis(headers[1].value, headers[1].value_len, ""));

    PARSE("Host: example.com\r\nCookie: \r\n\r\n", 1, 0, "slowloris");
    ok(num_headers == 2);
    ok(bufis(headers[0].name, headers[0].name_len, "Host"));
    ok(bufis(headers[0].value, headers[0].value_len, "example.com"));
    ok(bufis(headers[1].name, headers[1].name_len, "Cookie"));
    ok(bufis(headers[1].value, headers[1].value_len, ""));

    PARSE("Host: example.com\r\nCookie: \r\n\r", 0, -2, "partial");

    PARSE("Host: e\7fample.com\r\nCookie: \r\n\r", 0, -1, "error");

#undef PARSE
}