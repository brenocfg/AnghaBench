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
struct TYPE_3__ {int /*<<< orphan*/  users; } ;
typedef  TYPE_1__ UsersTable ;
typedef  int /*<<< orphan*/  Hashtable_PairFunction ;

/* Variables and functions */
 int /*<<< orphan*/  Hashtable_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

inline void UsersTable_foreach(UsersTable* this, Hashtable_PairFunction f, void* userData) {
   Hashtable_foreach(this->users, f, userData);
}