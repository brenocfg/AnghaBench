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
struct pctrie {int dummy; } ;

/* Variables and functions */
 int M_NOWAIT ; 
 int M_USE_RESERVE ; 
 scalar_t__ curproc ; 
 scalar_t__ pageproc ; 
 int /*<<< orphan*/  swpctrie_zone ; 
 void* uma_zalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *
swblk_trie_alloc(struct pctrie *ptree)
{

	return (uma_zalloc(swpctrie_zone, M_NOWAIT | (curproc == pageproc ?
	    M_USE_RESERVE : 0)));
}