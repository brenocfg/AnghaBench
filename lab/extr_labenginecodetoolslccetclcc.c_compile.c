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

/* Variables and functions */
 int /*<<< orphan*/  append (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av ; 
 int callsys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clist ; 
 int /*<<< orphan*/  com ; 
 int /*<<< orphan*/  compose (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compile(char *src, char *dst) {
	compose(com, clist, append(src, 0), append(dst, 0));
	return callsys(av);
}