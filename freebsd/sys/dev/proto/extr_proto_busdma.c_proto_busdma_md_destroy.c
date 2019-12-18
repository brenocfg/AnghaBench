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
struct proto_md {int /*<<< orphan*/ * virtaddr; } ;
struct proto_busdma {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int proto_busdma_md_destroy_internal (struct proto_busdma*,struct proto_md*) ; 

__attribute__((used)) static int
proto_busdma_md_destroy(struct proto_busdma *busdma, struct proto_md *md)
{

	if (md->virtaddr != NULL)
		return (ENXIO);
	return (proto_busdma_md_destroy_internal(busdma, md));
}