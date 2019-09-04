#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* set_error_message ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  userdata; TYPE_1__ hooks; } ;
typedef  TYPE_2__ DeepmindContext ;

/* Variables and functions */
 scalar_t__ errno ; 
 long strtod (char const*,char**) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  va (char*,char const*) ; 

__attribute__((used)) static int parse_double(const char* s, double* out, DeepmindContext* ctx) {
  errno = 0;
  char* e;
  long int val = strtod(s, &e);
  if (e != s && *e == '\0' && errno == 0) {
    *out = val;
    return 0;
  } else {
    ctx->hooks.set_error_message(ctx->userdata,
                                 va("Invalid double arg %s\n", s));
    return -1;
  }
}