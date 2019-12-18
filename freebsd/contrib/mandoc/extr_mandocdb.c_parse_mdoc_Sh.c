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
struct roff_node {scalar_t__ sec; scalar_t__ type; } ;
struct roff_meta {int dummy; } ;
struct mpage {int dummy; } ;

/* Variables and functions */
 scalar_t__ ROFFT_HEAD ; 
 scalar_t__ SEC_CUSTOM ; 

__attribute__((used)) static int
parse_mdoc_Sh(struct mpage *mpage, const struct roff_meta *meta,
	const struct roff_node *n)
{

	return n->sec == SEC_CUSTOM && n->type == ROFFT_HEAD;
}