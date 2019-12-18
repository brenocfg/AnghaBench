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
struct agp_segment_priv {int dummy; } ;
struct agp_client {int num_segments; struct agp_segment_priv** segments; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,struct agp_segment_priv**,int,struct agp_client*) ; 
 int /*<<< orphan*/  agp_remove_seg_from_client (struct agp_client*) ; 

__attribute__((used)) static void agp_add_seg_to_client(struct agp_client *client,
			       struct agp_segment_priv ** seg, int num_segments)
{
	struct agp_segment_priv **prev_seg;

	prev_seg = client->segments;

	if (prev_seg != NULL)
		agp_remove_seg_from_client(client);

	DBG("Adding seg %p (%d segments) to client %p", seg, num_segments, client);
	client->num_segments = num_segments;
	client->segments = seg;
}