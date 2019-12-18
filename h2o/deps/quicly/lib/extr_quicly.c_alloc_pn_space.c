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
typedef  int /*<<< orphan*/  uint8_t ;
struct st_quicly_pn_space_t {scalar_t__ unacked_count; scalar_t__ next_expected_packet_number; int /*<<< orphan*/  largest_pn_received_at; int /*<<< orphan*/  ack_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_MAX ; 
 struct st_quicly_pn_space_t* malloc (size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  quicly_ranges_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct st_quicly_pn_space_t *alloc_pn_space(size_t sz)
{
    struct st_quicly_pn_space_t *space;

    if ((space = malloc(sz)) == NULL)
        return NULL;

    quicly_ranges_init(&space->ack_queue);
    space->largest_pn_received_at = INT64_MAX;
    space->next_expected_packet_number = 0;
    space->unacked_count = 0;
    if (sz != sizeof(*space))
        memset((uint8_t *)space + sizeof(*space), 0, sz - sizeof(*space));

    return space;
}