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
struct http_parser_url {int port; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int http_parser_parse_url (char*,int,int /*<<< orphan*/ ,struct http_parser_url*) ; 
 int /*<<< orphan*/  http_parser_url_init (struct http_parser_url*) ; 
 int /*<<< orphan*/  stderr ; 

void
test_no_overflow_parse_url (void)
{
  int rv;
  struct http_parser_url u;

  http_parser_url_init(&u);
  rv = http_parser_parse_url("http://example.com:8001", 22, 0, &u);

  if (rv != 0) {
    fprintf(stderr,
            "\n*** test_no_overflow_parse_url invalid return value=%d\n",
            rv);
    abort();
  }

  if (u.port != 800) {
    fprintf(stderr,
            "\n*** test_no_overflow_parse_url invalid port number=%d\n",
            u.port);
    abort();
  }
}