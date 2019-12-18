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
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  collpri_t ;

/* Variables and functions */
 int /*<<< orphan*/  INTERR ; 
 size_t numpri ; 
 int /*<<< orphan*/ * prilist ; 

__attribute__((used)) static collpri_t *
get_pri(int32_t ref)
{
	if ((ref < 0) || (ref > numpri)) {
		INTERR;
		return (NULL);
	}
	return (&prilist[ref]);
}