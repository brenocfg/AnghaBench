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
 scalar_t__ HPE_INVALID_CONTENT_LENGTH ; 
 scalar_t__ HPE_OK ; 
 scalar_t__ HTTP_PARSER_ERRNO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HTTP_RESPONSE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  http_parser_execute (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  http_parser_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  settings_null ; 

__attribute__((used)) static void
test_content_length_overflow (const char *buf, size_t buflen, int expect_ok)
{
  http_parser parser;
  http_parser_init(&parser, HTTP_RESPONSE);
  http_parser_execute(&parser, &settings_null, buf, buflen);

  if (expect_ok)
    assert(HTTP_PARSER_ERRNO(&parser) == HPE_OK);
  else
    assert(HTTP_PARSER_ERRNO(&parser) == HPE_INVALID_CONTENT_LENGTH);
}