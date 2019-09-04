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
 int /*<<< orphan*/  Field_Complete () ; 
 int /*<<< orphan*/  FindMatches ; 
 int /*<<< orphan*/  Key_KeynameCompletion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintMatches ; 
 scalar_t__ matchCount ; 
 scalar_t__* shortestMatch ; 

void Field_CompleteKeyname( void )
{
	matchCount = 0;
	shortestMatch[ 0 ] = 0;

	Key_KeynameCompletion( FindMatches );

	if( !Field_Complete( ) )
		Key_KeynameCompletion( PrintMatches );
}