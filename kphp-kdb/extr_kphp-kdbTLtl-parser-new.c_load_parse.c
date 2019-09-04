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
struct parse {size_t pos; size_t len; int /*<<< orphan*/ * text; } ;

/* Variables and functions */
 int /*<<< orphan*/  curch ; 
 struct parse parse ; 

void load_parse (struct parse _parse) {
  parse = _parse;
  curch = parse.pos > parse.len ? 0:  parse.text[parse.pos] ;
}