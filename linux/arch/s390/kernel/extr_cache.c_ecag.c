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
 int /*<<< orphan*/  ECAG_CACHE_ATTRIBUTE ; 
 unsigned long __ecag (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline unsigned long ecag(int ai, int li, int ti)
{
	return __ecag(ECAG_CACHE_ATTRIBUTE, ai << 4 | li << 1 | ti);
}