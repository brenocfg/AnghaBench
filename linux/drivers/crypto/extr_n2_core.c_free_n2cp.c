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
struct TYPE_2__ {struct n2_crypto* ino_table; } ;
struct n2_crypto {TYPE_1__ cwq_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct n2_crypto*) ; 

__attribute__((used)) static void free_n2cp(struct n2_crypto *np)
{
	kfree(np->cwq_info.ino_table);
	np->cwq_info.ino_table = NULL;

	kfree(np);
}