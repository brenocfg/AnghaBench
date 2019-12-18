#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct updn_node {int rank; int /*<<< orphan*/  id; TYPE_1__* sw; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_node; } ;
typedef  TYPE_1__ osm_switch_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_ntoh64 (int /*<<< orphan*/ ) ; 
 struct updn_node* malloc (int) ; 
 int /*<<< orphan*/  memset (struct updn_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  osm_node_get_node_guid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct updn_node *create_updn_node(osm_switch_t * sw)
{
	struct updn_node *u;

	u = malloc(sizeof(*u));
	if (!u)
		return NULL;
	memset(u, 0, sizeof(*u));
	u->sw = sw;
	u->id = cl_ntoh64(osm_node_get_node_guid(sw->p_node));
	u->rank = 0xffffffff;
	return u;
}