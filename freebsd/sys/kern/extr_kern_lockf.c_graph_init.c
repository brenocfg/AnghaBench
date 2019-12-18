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
struct owner_vertex {int dummy; } ;
struct owner_graph {int g_space; scalar_t__ g_gen; void* g_indexbuf; scalar_t__ g_size; void* g_vertices; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_LOCKF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 void* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct owner_graph *
graph_init(struct owner_graph *g)
{

	g->g_vertices = malloc(10 * sizeof(struct owner_vertex *),
	    M_LOCKF, M_WAITOK);
	g->g_size = 0;
	g->g_space = 10;
	g->g_indexbuf = malloc(g->g_space * sizeof(int), M_LOCKF, M_WAITOK);
	g->g_gen = 0;

	return (g);
}