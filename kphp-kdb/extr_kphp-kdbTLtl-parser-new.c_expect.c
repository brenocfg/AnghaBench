#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* ptr; scalar_t__ type; scalar_t__ len; } ;
struct TYPE_4__ {TYPE_1__ lex; } ;

/* Variables and functions */
 scalar_t__ lex_error ; 
 scalar_t__ lex_none ; 
 scalar_t__ memcmp (char*,void*,scalar_t__) ; 
 TYPE_2__ parse ; 
 int /*<<< orphan*/  parse_error (char*) ; 
 int /*<<< orphan*/  parse_lex () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int expect (char *s) {
  if (!parse.lex.ptr || parse.lex.ptr == (void *)-1 || parse.lex.type == lex_error || parse.lex.type == lex_none || parse.lex.len != strlen (s) || memcmp (s, parse.lex.ptr, parse.lex.len)) {
    static char buf[1000];
    sprintf (buf, "Expected %s", s);
    parse_error (buf);
    return -1;
  } else {
    parse_lex ();
  }
  return 1;
}