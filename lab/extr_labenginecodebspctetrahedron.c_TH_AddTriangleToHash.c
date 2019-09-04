#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* hashnext; int /*<<< orphan*/ * edges; } ;
typedef  TYPE_1__ th_triangle_t ;
struct TYPE_5__ {TYPE_1__** trianglehash; } ;

/* Variables and functions */
 int TRIANGLEHASH_SIZE ; 
 int abs (int /*<<< orphan*/ ) ; 
 TYPE_2__ thworld ; 

void TH_AddTriangleToHash(th_triangle_t *tri)
{
	int hashvalue;

	hashvalue = (abs(tri->edges[0]) + abs(tri->edges[1]) + abs(tri->edges[2])) & (TRIANGLEHASH_SIZE-1);
	tri->hashnext = thworld.trianglehash[hashvalue];
	thworld.trianglehash[hashvalue] = tri;
}