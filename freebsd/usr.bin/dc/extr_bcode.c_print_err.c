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
struct value {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  obase; } ;

/* Variables and functions */
 TYPE_1__ bmachine ; 
 int /*<<< orphan*/  print_value (int /*<<< orphan*/ ,struct value*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 struct value* tos () ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
print_err(void)
{
	struct value *value = tos();
	if (value != NULL) {
		print_value(stderr, value, "", bmachine.obase);
		(void)putc('\n', stderr);
	}
	else
		warnx("stack empty");
}