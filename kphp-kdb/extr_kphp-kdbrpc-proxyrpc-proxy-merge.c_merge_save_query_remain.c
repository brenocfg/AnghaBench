#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct gather {int saved_query_len; void* saved_query; TYPE_1__* header; } ;
struct TYPE_6__ {int /*<<< orphan*/  new_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  h; } ;
struct TYPE_4__ {int /*<<< orphan*/  actor_id; } ;

/* Variables and functions */
 TYPE_3__* CC ; 
 TYPE_2__* CQ ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tl_fetch_lookup_data (void*,int) ; 
 int tl_fetch_unread () ; 

void merge_save_query_remain (struct gather *G) {
  G->header = malloc (sizeof (*G->header));
  memcpy (G->header, &CQ->h, sizeof (*G->header));
  G->header->actor_id = CC->new_id;
  G->saved_query_len = tl_fetch_unread ();
  G->saved_query = malloc (G->saved_query_len);
  tl_fetch_lookup_data (G->saved_query, G->saved_query_len);
}