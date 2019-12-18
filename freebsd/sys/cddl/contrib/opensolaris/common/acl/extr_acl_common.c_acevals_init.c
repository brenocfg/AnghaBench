#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_4__ {int /*<<< orphan*/  key; void* mask; void* denied; void* allowed; } ;
typedef  TYPE_1__ acevals_t ;

/* Variables and functions */
 void* ACE_MASK_UNDEFINED ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 

__attribute__((used)) static void
acevals_init(acevals_t *vals, uid_t key)
{
	bzero(vals, sizeof (*vals));
	vals->allowed = ACE_MASK_UNDEFINED;
	vals->denied = ACE_MASK_UNDEFINED;
	vals->mask = ACE_MASK_UNDEFINED;
	vals->key = key;
}