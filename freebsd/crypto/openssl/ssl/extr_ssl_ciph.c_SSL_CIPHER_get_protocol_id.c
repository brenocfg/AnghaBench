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
typedef  int uint16_t ;
struct TYPE_3__ {int id; } ;
typedef  TYPE_1__ SSL_CIPHER ;

/* Variables and functions */

uint16_t SSL_CIPHER_get_protocol_id(const SSL_CIPHER *c)
{
    return c->id & 0xFFFF;
}