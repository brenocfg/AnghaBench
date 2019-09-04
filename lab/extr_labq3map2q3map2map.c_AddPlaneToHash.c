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
struct TYPE_4__ {struct TYPE_4__* hash_chain; int /*<<< orphan*/  dist; } ;
typedef  TYPE_1__ plane_t ;

/* Variables and functions */
 int PLANE_HASHES ; 
 scalar_t__ fabs (int /*<<< orphan*/ ) ; 
 TYPE_1__** planehash ; 

void AddPlaneToHash( plane_t *p ){
	int hash;


	hash = ( PLANE_HASHES - 1 ) & (int) fabs( p->dist );

	p->hash_chain = planehash[hash];
	planehash[hash] = p;
}