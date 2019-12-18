#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pos; int len; int* text; scalar_t__ line_pos; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 int curch ; 
 TYPE_1__ parse ; 

char nextch (void) {
  if (parse.pos < parse.len - 1) {
    curch = parse.text[++parse.pos];
  } else {
    curch = 0;
  }
  if (curch == 10) {
    parse.line ++;
    parse.line_pos = 0;
  } else {
    if (curch) {
      parse.line_pos ++;
    }
  }
  return curch;
}