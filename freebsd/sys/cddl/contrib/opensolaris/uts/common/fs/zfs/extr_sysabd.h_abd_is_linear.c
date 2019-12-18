#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int abd_flags; } ;
typedef  TYPE_1__ abd_t ;

/* Variables and functions */
 int ABD_FLAG_LINEAR ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 

inline boolean_t
abd_is_linear(abd_t *abd)
{
	return ((abd->abd_flags & ABD_FLAG_LINEAR) != 0 ? B_TRUE : B_FALSE);
}