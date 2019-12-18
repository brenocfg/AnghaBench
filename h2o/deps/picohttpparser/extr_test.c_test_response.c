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
struct phr_header {char const* name; size_t name_len; char const* value; size_t value_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE (char*,scalar_t__,int,char*) ; 
 int bufis (char const*,size_t,char*) ; 
 int /*<<< orphan*/  ok (int) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void test_response(void)
{
    int minor_version;
    int status;
    const char *msg;
    size_t msg_len;
    struct phr_header headers[4];
    size_t num_headers;

#define PARSE(s, last_len, exp, comment)                                                                                           \
    do {                                                                                                                           \
        note(comment);                                                                                                             \
        num_headers = sizeof(headers) / sizeof(headers[0]);                                                                        \
        ok(phr_parse_response(s, strlen(s), &minor_version, &status, &msg, &msg_len, headers, &num_headers, last_len) ==           \
           (exp == 0 ? strlen(s) : exp));                                                                                          \
    } while (0)

    PARSE("HTTP/1.0 200 OK\r\n\r\n", 0, 0, "simple");
    ok(num_headers == 0);
    ok(status == 200);
    ok(minor_version == 0);
    ok(bufis(msg, msg_len, "OK"));

    PARSE("HTTP/1.0 200 OK\r\n\r", 0, -2, "partial");

    PARSE("HTTP/1.1 200 OK\r\nHost: example.com\r\nCookie: \r\n\r\n", 0, 0, "parse headers");
    ok(num_headers == 2);
    ok(minor_version == 1);
    ok(status == 200);
    ok(bufis(msg, msg_len, "OK"));
    ok(bufis(headers[0].name, headers[0].name_len, "Host"));
    ok(bufis(headers[0].value, headers[0].value_len, "example.com"));
    ok(bufis(headers[1].name, headers[1].name_len, "Cookie"));
    ok(bufis(headers[1].value, headers[1].value_len, ""));

    PARSE("HTTP/1.0 200 OK\r\nfoo: \r\nfoo: b\r\n  \tc\r\n\r\n", 0, 0, "parse multiline");
    ok(num_headers == 3);
    ok(minor_version == 0);
    ok(status == 200);
    ok(bufis(msg, msg_len, "OK"));
    ok(bufis(headers[0].name, headers[0].name_len, "foo"));
    ok(bufis(headers[0].value, headers[0].value_len, ""));
    ok(bufis(headers[1].name, headers[1].name_len, "foo"));
    ok(bufis(headers[1].value, headers[1].value_len, "b"));
    ok(headers[2].name == NULL);
    ok(bufis(headers[2].value, headers[2].value_len, "  \tc"));

    PARSE("HTTP/1.0 500 Internal Server Error\r\n\r\n", 0, 0, "internal server error");
    ok(num_headers == 0);
    ok(minor_version == 0);
    ok(status == 500);
    ok(bufis(msg, msg_len, "Internal Server Error"));
    ok(msg_len == sizeof("Internal Server Error") - 1);

    PARSE("H", 0, -2, "incomplete 1");
    PARSE("HTTP/1.", 0, -2, "incomplete 2");
    PARSE("HTTP/1.1", 0, -2, "incomplete 3");
    ok(minor_version == -1);
    PARSE("HTTP/1.1 ", 0, -2, "incomplete 4");
    ok(minor_version == 1);
    PARSE("HTTP/1.1 2", 0, -2, "incomplete 5");
    PARSE("HTTP/1.1 200", 0, -2, "incomplete 6");
    ok(status == 0);
    PARSE("HTTP/1.1 200 ", 0, -2, "incomplete 7");
    ok(status == 200);
    PARSE("HTTP/1.1 200 O", 0, -2, "incomplete 8");
    PARSE("HTTP/1.1 200 OK\r", 0, -2, "incomplete 9");
    ok(msg == NULL);
    PARSE("HTTP/1.1 200 OK\r\n", 0, -2, "incomplete 10");
    ok(bufis(msg, msg_len, "OK"));
    PARSE("HTTP/1.1 200 OK\n", 0, -2, "incomplete 11");
    ok(bufis(msg, msg_len, "OK"));

    PARSE("HTTP/1.1 200 OK\r\nA: 1\r", 0, -2, "incomplete 11");
    ok(num_headers == 0);
    PARSE("HTTP/1.1 200 OK\r\nA: 1\r\n", 0, -2, "incomplete 12");
    ok(num_headers == 1);
    ok(bufis(headers[0].name, headers[0].name_len, "A"));
    ok(bufis(headers[0].value, headers[0].value_len, "1"));

    PARSE("HTTP/1.0 200 OK\r\n\r", strlen("HTTP/1.0 200 OK\r\n\r") - 1, -2, "slowloris (incomplete)");
    PARSE("HTTP/1.0 200 OK\r\n\r\n", strlen("HTTP/1.0 200 OK\r\n\r\n") - 1, 0, "slowloris (complete)");

    PARSE("HTTP/1. 200 OK\r\n\r\n", 0, -1, "invalid http version");
    PARSE("HTTP/1.2z 200 OK\r\n\r\n", 0, -1, "invalid http version 2");
    PARSE("HTTP/1.1  OK\r\n\r\n", 0, -1, "no status code");

    PARSE("HTTP/1.1 200 OK\r\nbar: \t b\t \t\r\n\r\n", 0, 0, "exclude leading and trailing spaces in header value");
    ok(bufis(headers[0].value, headers[0].value_len, "b"));

#undef PARSE
}