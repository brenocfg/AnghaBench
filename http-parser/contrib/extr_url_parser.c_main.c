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
struct http_parser_url {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_url (char*,struct http_parser_url*) ; 
 int http_parser_parse_url (char*,int,int,struct http_parser_url*) ; 
 int /*<<< orphan*/  http_parser_url_init (struct http_parser_url*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

int main(int argc, char ** argv) {
  struct http_parser_url u;
  int len, connect, result;

  if (argc != 3) {
    printf("Syntax : %s connect|get url\n", argv[0]);
    return 1;
  }
  len = strlen(argv[2]);
  connect = strcmp("connect", argv[1]) == 0 ? 1 : 0;
  printf("Parsing %s, connect %d\n", argv[2], connect);

  http_parser_url_init(&u);
  result = http_parser_parse_url(argv[2], len, connect, &u);
  if (result != 0) {
    printf("Parse error : %d\n", result);
    return result;
  }
  printf("Parse ok, result : \n");
  dump_url(argv[2], &u);
  return 0;
}