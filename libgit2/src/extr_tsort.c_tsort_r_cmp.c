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
typedef  int (* git__tsort_cmp ) (void const*,void const*) ;

/* Variables and functions */
 int stub1 (void const*,void const*) ; 

__attribute__((used)) static int tsort_r_cmp(const void *a, const void *b, void *payload)
{
	return ((git__tsort_cmp)payload)(a, b);
}