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
struct packed_git {int pack_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct packed_git*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  st_add (int,int) ; 
 struct packed_git* xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct packed_git *alloc_packed_git(int extra)
{
	struct packed_git *p = xmalloc(st_add(sizeof(*p), extra));
	memset(p, 0, sizeof(*p));
	p->pack_fd = -1;
	return p;
}