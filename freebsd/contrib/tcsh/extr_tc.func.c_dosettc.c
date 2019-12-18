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
struct command {int dummy; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  GetTermCaps () ; 
 int /*<<< orphan*/  GotTermCaps ; 
 int /*<<< orphan*/  SetTC (char*,char*) ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int /*<<< orphan*/  cleanup_push (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_until (char*) ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ *) ; 
 char* strsave (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfree ; 

void
dosettc(Char **v, struct command *c)
{
    char    *tv[2];

    USE(c);
    if (!GotTermCaps)
	GetTermCaps();

    tv[0] = strsave(short2str(v[1]));
    cleanup_push(tv[0], xfree);
    tv[1] = strsave(short2str(v[2]));
    cleanup_push(tv[1], xfree);
    SetTC(tv[0], tv[1]);
    cleanup_until(tv[0]);
}