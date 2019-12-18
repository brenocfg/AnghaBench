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
 scalar_t__ S_ISDIR (unsigned int) ; 
 scalar_t__ S_ISLNK (unsigned int) ; 

__attribute__((used)) static int score_differs(unsigned mode1, unsigned mode2)
{
	int score;

	if (S_ISDIR(mode1) != S_ISDIR(mode2))
		score = -100;
	else if (S_ISLNK(mode1) != S_ISLNK(mode2))
		score = -50;
	else
		score = -5;
	return score;
}