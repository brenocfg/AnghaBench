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
struct TYPE_4__ {TYPE_3__* stats; TYPE_2__* writepack; } ;
typedef  TYPE_1__ foreach_data ;
struct TYPE_6__ {size_t received_bytes; } ;
struct TYPE_5__ {int (* append ) (TYPE_2__*,void*,size_t,TYPE_3__*) ;} ;

/* Variables and functions */
 int stub1 (TYPE_2__*,void*,size_t,TYPE_3__*) ; 

__attribute__((used)) static int foreach_cb(void *buf, size_t len, void *payload)
{
	foreach_data *data = (foreach_data*)payload;

	data->stats->received_bytes += len;
	return data->writepack->append(data->writepack, buf, len, data->stats);
}