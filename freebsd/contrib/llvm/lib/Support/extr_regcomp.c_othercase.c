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
typedef  char uch ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isalpha (int) ; 
 scalar_t__ islower (int) ; 
 scalar_t__ isupper (int) ; 
 scalar_t__ tolower (int) ; 
 scalar_t__ toupper (int) ; 

__attribute__((used)) static char			/* if no counterpart, return ch */
othercase(int ch)
{
	ch = (uch)ch;
	assert(isalpha(ch));
	if (isupper(ch))
		return ((uch)tolower(ch));
	else if (islower(ch))
		return ((uch)toupper(ch));
	else			/* peculiar, but could happen */
		return(ch);
}