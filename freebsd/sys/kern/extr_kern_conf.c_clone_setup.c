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
struct clonedevs {int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct clonedevs* malloc (int,int /*<<< orphan*/ ,int) ; 

void
clone_setup(struct clonedevs **cdp)
{

	*cdp = malloc(sizeof **cdp, M_DEVBUF, M_WAITOK | M_ZERO);
	LIST_INIT(&(*cdp)->head);
}