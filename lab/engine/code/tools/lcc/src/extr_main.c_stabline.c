#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* stabline ) (TYPE_1__*) ;} ;
struct TYPE_5__ {scalar_t__ file; scalar_t__ y; } ;
typedef  TYPE_1__ Coordinate ;

/* Variables and functions */
 int /*<<< orphan*/  comment ; 
 scalar_t__ currentfile ; 
 scalar_t__ currentline ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (scalar_t__,char*) ; 
 int /*<<< orphan*/  print (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * srcfp ; 
 scalar_t__ srcpos ; 
 TYPE_4__ stabIR ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void stabline(Coordinate *cp) {
	if (cp->file && cp->file != currentfile) {
		if (srcfp)
			fclose(srcfp);
		currentfile = cp->file;
		srcfp = fopen(currentfile, "r");
		srcpos = 0;
		currentline = 0;
	}
	if (currentline != cp->y && srcfp) {
		char buf[512];
		if (srcpos > cp->y) {
			rewind(srcfp);
			srcpos = 0;
		}
		for ( ; srcpos < cp->y; srcpos++)
			if (fgets(buf, sizeof buf, srcfp) == NULL) {
				fclose(srcfp);
				srcfp = NULL;
				break;
			}
		if (srcfp && srcpos == cp->y)
			print("%s%s", comment, buf);
	}
	currentline = cp->y;
	if (stabIR.stabline)
		(*stabIR.stabline)(cp);
}