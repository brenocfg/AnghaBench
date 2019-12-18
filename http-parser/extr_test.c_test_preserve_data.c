#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* data; } ;
typedef  TYPE_1__ http_parser ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_REQUEST ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  http_parser_init (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
test_preserve_data (void)
{
  char my_data[] = "application-specific data";
  http_parser parser;
  parser.data = my_data;
  http_parser_init(&parser, HTTP_REQUEST);
  if (parser.data != my_data) {
    printf("\n*** parser.data not preserved accross http_parser_init ***\n\n");
    abort();
  }
}