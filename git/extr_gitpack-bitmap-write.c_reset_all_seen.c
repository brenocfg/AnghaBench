#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int ADDED ; 
 int SEEN ; 
 int SHOWN ; 
 TYPE_1__** seen_objects ; 
 unsigned int seen_objects_nr ; 

__attribute__((used)) static inline void reset_all_seen(void)
{
	unsigned int i;
	for (i = 0; i < seen_objects_nr; ++i) {
		seen_objects[i]->flags &= ~(SEEN | ADDED | SHOWN);
	}
	seen_objects_nr = 0;
}