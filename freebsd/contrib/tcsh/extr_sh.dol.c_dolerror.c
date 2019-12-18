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
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int ERR_NAME ; 
 int ERR_RANGE ; 
 int /*<<< orphan*/  setname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  short2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderror (int) ; 

__attribute__((used)) static void
dolerror(Char *s)
{
    setname(short2str(s));
    stderror(ERR_NAME | ERR_RANGE);
}