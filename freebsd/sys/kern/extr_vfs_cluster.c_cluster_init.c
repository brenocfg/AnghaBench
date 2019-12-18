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

/* Variables and functions */
 int /*<<< orphan*/  cluster_pbuf_zone ; 
 int nswbuf ; 
 int /*<<< orphan*/  pbuf_zsecond_create (char*,int) ; 

__attribute__((used)) static void
cluster_init(void *dummy)
{

	cluster_pbuf_zone = pbuf_zsecond_create("clpbuf", nswbuf / 2);
}