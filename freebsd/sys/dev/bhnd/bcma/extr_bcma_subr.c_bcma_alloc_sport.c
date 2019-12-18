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
struct bcma_sport {int /*<<< orphan*/  sp_maps; scalar_t__ sp_num_maps; int /*<<< orphan*/  sp_type; int /*<<< orphan*/  sp_num; } ;
typedef  int /*<<< orphan*/  bhnd_port_type ;
typedef  int /*<<< orphan*/  bcma_pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_BHND ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct bcma_sport* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct bcma_sport *
bcma_alloc_sport(bcma_pid_t port_num, bhnd_port_type port_type)
{
	struct bcma_sport *sport;
	
	sport = malloc(sizeof(struct bcma_sport), M_BHND, M_NOWAIT);
	if (sport == NULL)
		return NULL;
	
	sport->sp_num = port_num;
	sport->sp_type = port_type;
	sport->sp_num_maps = 0;
	STAILQ_INIT(&sport->sp_maps);

	return sport;
}