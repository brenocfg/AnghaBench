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
struct addr_tree_node {scalar_t__ net; int /*<<< orphan*/  addrlen; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int sockaddr_cmp_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int addr_tree_compare(const void* k1, const void* k2)
{
        struct addr_tree_node* n1 = (struct addr_tree_node*)k1;
        struct addr_tree_node* n2 = (struct addr_tree_node*)k2;
        int r = sockaddr_cmp_addr(&n1->addr, n1->addrlen, &n2->addr,
                n2->addrlen);
        if(r != 0) return r;
        if(n1->net < n2->net)
                return -1;
        if(n1->net > n2->net)
                return 1;
        return 0;
}