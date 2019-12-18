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
struct st_quicly_max_streams_t {int /*<<< orphan*/  blocked_sender; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_maxsender_init (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void init_max_streams(struct st_quicly_max_streams_t *m)
{
    m->count = 0;
    quicly_maxsender_init(&m->blocked_sender, -1);
}