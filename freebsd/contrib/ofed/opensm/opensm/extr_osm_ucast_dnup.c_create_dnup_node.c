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
struct dnup_node {int rank; int /*<<< orphan*/ * sw; } ;
typedef  int /*<<< orphan*/  osm_switch_t ;

/* Variables and functions */
 struct dnup_node* malloc (int) ; 
 int /*<<< orphan*/  memset (struct dnup_node*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dnup_node *create_dnup_node(osm_switch_t * sw)
{
	struct dnup_node *u;

	u = malloc(sizeof(*u));
	if (!u)
		return NULL;
	memset(u, 0, sizeof(*u));
	u->sw = sw;
	u->rank = 0xffffffff;
	return u;
}