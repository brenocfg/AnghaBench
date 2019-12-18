#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int hash_size; int key_material_len; int iv_size; } ;
struct tlsv1_client {scalar_t__ state; TYPE_1__ rl; } ;

/* Variables and functions */
 scalar_t__ CLIENT_HELLO ; 
 scalar_t__ SERVER_HELLO ; 

int tlsv1_client_get_keyblock_size(struct tlsv1_client *conn)
{
	if (conn->state == CLIENT_HELLO || conn->state == SERVER_HELLO)
		return -1;

	return 2 * (conn->rl.hash_size + conn->rl.key_material_len +
		    conn->rl.iv_size);
}