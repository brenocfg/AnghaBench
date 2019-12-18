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
 int /*<<< orphan*/  BEAUTIFY ; 
 int /*<<< orphan*/  boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setboolean (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigbuf ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intSYS(int signo)
{
	setboolean(value(BEAUTIFY), !boolean(value(BEAUTIFY)));
	longjmp(sigbuf, 1);
}