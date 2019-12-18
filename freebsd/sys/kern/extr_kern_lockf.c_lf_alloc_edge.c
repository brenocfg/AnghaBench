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
struct lockf_edge {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_LOCKF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 struct lockf_edge* malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct lockf_edge *
lf_alloc_edge(void)
{

	return (malloc(sizeof(struct lockf_edge), M_LOCKF, M_WAITOK|M_ZERO));
}