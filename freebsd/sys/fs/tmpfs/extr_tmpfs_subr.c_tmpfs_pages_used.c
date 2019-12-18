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
typedef  size_t const uintmax_t ;
struct tmpfs_node {int dummy; } ;
struct tmpfs_mount {size_t tm_pages_used; scalar_t__ tm_nodes_inuse; } ;
struct tmpfs_dirent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t howmany (size_t const,int /*<<< orphan*/ ) ; 

size_t
tmpfs_pages_used(struct tmpfs_mount *tmp)
{
	const size_t node_size = sizeof(struct tmpfs_node) +
	    sizeof(struct tmpfs_dirent);
	size_t meta_pages;

	meta_pages = howmany((uintmax_t)tmp->tm_nodes_inuse * node_size,
	    PAGE_SIZE);
	return (meta_pages + tmp->tm_pages_used);
}