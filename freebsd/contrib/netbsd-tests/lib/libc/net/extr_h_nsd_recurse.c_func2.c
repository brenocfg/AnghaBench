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
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ ns_dtab ;

/* Variables and functions */
#define  func3 128 
 int nsdispatch (int /*<<< orphan*/ *,TYPE_1__ const*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  testsrc ; 

__attribute__((used)) static int
func2(void *rv, void *cb_data, va_list ap)
{
	static const ns_dtab dtab[] = {
		{ "test",	func3,		NULL },
		{ NULL, NULL, NULL }
	};
	int r;

	(void)printf("func2: enter\n");
	r = nsdispatch(NULL, dtab, "test", "test", testsrc);
	(void)printf("func2: exit\n");

	return r;
}