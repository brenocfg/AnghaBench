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
typedef  int /*<<< orphan*/  http_parser ;

/* Variables and functions */
 scalar_t__ HPE_UNEXPECTED_CONTENT_LENGTH ; 
 scalar_t__ HTTP_PARSER_ERRNO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTTP_REQUEST ; 
 int /*<<< orphan*/  HTTP_RESPONSE ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t http_parser_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  http_parser_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settings_null ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char const*) ; 

void
test_chunked_content_length_error (int req)
{
  http_parser parser;
  http_parser_init(&parser, req ? HTTP_REQUEST : HTTP_RESPONSE);
  size_t parsed;
  const char *buf;
  buf = req ?
    "GET / HTTP/1.1\r\n" :
    "HTTP/1.1 200 OK\r\n";
  parsed = http_parser_execute(&parser, &settings_null, buf, strlen(buf));
  assert(parsed == strlen(buf));

  buf = "Transfer-Encoding: chunked\r\nContent-Length: 1\r\n\r\n";
  size_t buflen = strlen(buf);

  parsed = http_parser_execute(&parser, &settings_null, buf, buflen);
  if (parsed != buflen) {
    assert(HTTP_PARSER_ERRNO(&parser) == HPE_UNEXPECTED_CONTENT_LENGTH);
    return;
  }

  fprintf(stderr,
          "\n*** Error expected but none in chunked content-length test ***\n");
  abort();
}