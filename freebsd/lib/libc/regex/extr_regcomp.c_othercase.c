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
typedef  int /*<<< orphan*/  wint_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iswalpha (int /*<<< orphan*/ ) ; 
 scalar_t__ iswlower (int /*<<< orphan*/ ) ; 
 scalar_t__ iswupper (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  towlower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  towupper (int /*<<< orphan*/ ) ; 

__attribute__((used)) static wint_t			/* if no counterpart, return ch */
othercase(wint_t ch)
{
	assert(iswalpha(ch));
	if (iswupper(ch))
		return(towlower(ch));
	else if (iswlower(ch))
		return(towupper(ch));
	else			/* peculiar, but could happen */
		return(ch);
}