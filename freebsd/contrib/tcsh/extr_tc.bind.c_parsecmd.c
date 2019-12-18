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
struct KeyFuncs {int /*<<< orphan*/  func; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  KEYCMD ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 struct KeyFuncs* FuncNames ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static  KEYCMD
parsecmd(Char *str)
{
    struct KeyFuncs *fp;

    for (fp = FuncNames; fp->name; fp++) {
	if (strcmp(short2str(str), fp->name) == 0) {
	    return (KEYCMD) fp->func;
	}
    }
    xprintf(CGETS(20, 3, "Bad command name: %S\n"), str);
    return 0;
}