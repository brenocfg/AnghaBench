#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  returns; int /*<<< orphan*/  entry; } ;
struct TYPE_5__ {scalar_t__ defined; } ;
typedef  TYPE_1__* Symbol ;
typedef  int /*<<< orphan*/  Apply ;

/* Variables and functions */
 int /*<<< orphan*/  CONST ; 
 int /*<<< orphan*/  EXTERN ; 
 scalar_t__ IR ; 
 int /*<<< orphan*/  attach (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chartype ; 
 TYPE_3__ events ; 
 int /*<<< orphan*/  ftype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 TYPE_1__* mksymbol (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qual (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ tracecall ; 
 scalar_t__ tracereturn ; 
 int /*<<< orphan*/  type_init (int,char**) ; 

void trace_init(int argc, char *argv[]) {
	int i;
	static int inited;

	if (inited)
		return;
	inited = 1;
	type_init(argc, argv);
	if (IR)
		for (i = 1; i < argc; i++)
			if (strncmp(argv[i], "-t", 2) == 0 &&  strchr(argv[i], '=') == NULL) {
				Symbol printer = mksymbol(EXTERN,
					argv[i][2] ? &argv[i][2] : "printf",
				ftype(inttype, ptr(qual(CONST, chartype))));
				printer->defined = 0;
				attach((Apply)tracecall,   printer, &events.entry);
				attach((Apply)tracereturn, printer, &events.returns);
				break;
			}
}