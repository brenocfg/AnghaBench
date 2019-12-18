#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rp_generator_t {TYPE_5__* client; TYPE_4__* src_req; } ;
struct TYPE_7__ {int /*<<< orphan*/  body; int /*<<< orphan*/  header; int /*<<< orphan*/  total; } ;
struct TYPE_10__ {TYPE_2__ bytes_written; int /*<<< orphan*/  timings; } ;
struct TYPE_6__ {int /*<<< orphan*/  body; int /*<<< orphan*/  header; int /*<<< orphan*/  total; } ;
struct TYPE_8__ {TYPE_1__ bytes_written; int /*<<< orphan*/  timestamps; } ;
struct TYPE_9__ {TYPE_3__ proxy_stats; } ;

/* Variables and functions */

__attribute__((used)) static void copy_stats(struct rp_generator_t *self)
{
    self->src_req->proxy_stats.timestamps = self->client->timings;
    self->src_req->proxy_stats.bytes_written.total = self->client->bytes_written.total;
    self->src_req->proxy_stats.bytes_written.header = self->client->bytes_written.header;
    self->src_req->proxy_stats.bytes_written.body = self->client->bytes_written.body;
}