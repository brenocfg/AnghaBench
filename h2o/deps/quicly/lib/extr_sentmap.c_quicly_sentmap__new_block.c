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
struct st_quicly_sent_block_t {struct st_quicly_sent_block_t* next; scalar_t__ next_insert_at; scalar_t__ num_entries; } ;
struct TYPE_3__ {struct st_quicly_sent_block_t* tail; struct st_quicly_sent_block_t* head; } ;
typedef  TYPE_1__ quicly_sentmap_t ;

/* Variables and functions */
 struct st_quicly_sent_block_t* malloc (int) ; 

struct st_quicly_sent_block_t *quicly_sentmap__new_block(quicly_sentmap_t *map)
{
    struct st_quicly_sent_block_t *block;

    if ((block = malloc(sizeof(*block))) == NULL)
        return NULL;

    block->next = NULL;
    block->num_entries = 0;
    block->next_insert_at = 0;
    if (map->tail != NULL) {
        map->tail->next = block;
        map->tail = block;
    } else {
        map->head = map->tail = block;
    }

    return block;
}