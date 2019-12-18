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
struct TYPE_2__ {scalar_t__ pos; int /*<<< orphan*/  line_pos; int /*<<< orphan*/  line; } ;

/* Variables and functions */
 scalar_t__ last_error ; 
 int /*<<< orphan*/  last_error_line ; 
 int /*<<< orphan*/  last_error_line_pos ; 
 scalar_t__ last_error_pos ; 
 TYPE_1__ parse ; 
 scalar_t__ strlen (scalar_t__) ; 
 int /*<<< orphan*/  zfree (scalar_t__,scalar_t__) ; 
 scalar_t__ zstrdup (char const*) ; 

void parse_error (const char *e) {
  if (parse.pos > last_error_pos) {
    last_error_pos = parse.pos;
    last_error_line = parse.line;
    last_error_line_pos = parse.line_pos;
    if (last_error) {
      zfree (last_error, strlen (last_error) + 1);
    }
    last_error = zstrdup (e);
  }
}