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
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  cchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_NORMAL ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  p_error (char*) ; 
 scalar_t__ setcchar (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static cchar_t *
makecchar(wchar_t in)
{
	static cchar_t cc;
	wchar_t wc[2];

	wc[0] = in;
	wc[1] = L'\0';

	if (setcchar(&cc, wc, A_NORMAL, 0, NULL) != OK)
		p_error("settchar(3) failure");

	return (&cc);
}